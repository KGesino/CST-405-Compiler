#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"

/* ------------ file-scope state ------------ */
static FILE* output;
static int tempReg = 0;

/* ------------ helpers ------------ */
static int getNextTemp() {
    int reg = tempReg++;
    if (tempReg > 7) tempReg = 0;   // reuse $t0-$t7
    return reg;
}

/* arrays: query 2D cols from symtab */
static int getArray2DCols(const char* name) {
    int rows, cols;
    getArray2DSizes(name, &rows, &cols);
    return cols;
}

/* forward decls */
static void genStmt(ASTNode* node);
static char* genExprToTemp(ASTNode* node, int* outTReg);
static void genFunction(ASTNode* func);
static void genFuncList(ASTNode* list);

/* -------- predeclare locals (and params) into current scope -------- */
static void predeclareBody(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case NODE_DECL:
            (void)addVar(node->data.name, "int");
            break;
        case NODE_ARRAY_DECL:
            (void)addArray(node->data.arrdecl.name, "int", node->data.arrdecl.size);
            break;
        case NODE_ARRAY2D_DECL:
            (void)addArray2D(node->data.arr2d_decl.name, "int",
                             node->data.arr2d_decl.rows, node->data.arr2d_decl.cols);
            break;
        case NODE_STMT_LIST:
            predeclareBody(node->data.stmtlist.stmt);
            predeclareBody(node->data.stmtlist.next);
            break;
        default:
            break;
    }
}

/* Safely walk a param_list which may be:
   - a single NODE_PARAM
   - or a NODE_PARAM_LIST chain linking NODE_PARAMs
*/
static int addParams(ASTNode* params) {
    int count = 0;
    ASTNode* p = params;

    while (p) {
        if (p->type == NODE_PARAM) {
            const char* name = p->data.param.name;
            const char* type = p->data.param.type;
            if (name && type) {
                addParameter((char*)name, (char*)type);
                count++;
            } else {
                fprintf(stderr, "Warning: skipped parameter with null name/type in addParams\n");
            }
            break;
        } else if (p->type == NODE_PARAM_LIST) {
            ASTNode* item = p->data.list.item;
            if (item && item->type == NODE_PARAM &&
                item->data.param.name && item->data.param.type) {
                addParameter(item->data.param.name, item->data.param.type);
                count++;
            } else {
                fprintf(stderr, "Warning: skipped parameter with null name/type in addParams\n");
            }
            p = p->data.list.next;
        } else {
            fprintf(stderr, "Warning: unexpected node type %d in addParams\n", p->type);
            break;
        }
    }
    return count;
}




/* compute stack bytes for locals in current scope */
static int localsBytes() {
    int n = getTotalStackBytes();
    return (n < 0) ? 0 : n;
}

/* ------------------ Expressions -> temps ------------------ */
static char* dupstr(const char* s) {
    char* r = (char*)malloc(strlen(s)+1);
    strcpy(r, s);
    return r;
}

static const char* tregName(int r) {
    static char buf[8];
    snprintf(buf, sizeof(buf), "$t%d", r);
    return buf;
}

/* Evaluate expression -> temp register */
static char* genExprToTemp(ASTNode* node, int* outTReg) {
    if (!node) {
        int dummy = getNextTemp();
        *outTReg = dummy;
        fprintf(output, "  # WARNING: null expr, loading 0 into %s\n", tregName(dummy));
        fprintf(output, "  li %s, 0\n", tregName(dummy));
        return dupstr(tregName(dummy));
    }
    switch (node->type) {
        /* --- integer literal --- */
        case NODE_NUM: {
            int r = getNextTemp();
            fprintf(output, "  li %s, %d\n", tregName(r), node->data.num);
            *outTReg = r;
            return dupstr(tregName(r));
        }

        /* --- float literal (NEW) --- */
        case NODE_FLOAT: {
            int r = getNextTemp();
            fprintf(output, "  # float literal %.6f\n", node->data.fnum);
            fprintf(output, "  li.s $f%d, %f\n", r, node->data.fnum);
            *outTReg = r;
            return dupstr(tregName(r));
        }

        case NODE_VAR: {
            int off = getVarOffset(node->data.name);
            if (off < 0) { fprintf(stderr, "Var %s undeclared\n", node->data.name); exit(1); }
            int r = getNextTemp();
            fprintf(output, "  lw %s, %d($sp)\n", tregName(r), off);
            *outTReg = r;
            return dupstr(tregName(r));
        }

        case NODE_ARRAY_ACCESS: {
            int base = getVarOffset(node->data.arraccess.name);
            if (base < 0) { fprintf(stderr, "Array %s undeclared\n", node->data.arraccess.name); exit(1); }
            int idxR; char* idx = genExprToTemp(node->data.arraccess.index, &idxR);
            int addrR = getNextTemp();
            fprintf(output, "  addi %s, $sp, %d\n", tregName(addrR), base);
            fprintf(output, "  sll %s, %s, 2\n", tregName(idxR), tregName(idxR));
            fprintf(output, "  add %s, %s, %s\n", tregName(addrR), tregName(addrR), tregName(idxR));
            fprintf(output, "  lw %s, 0(%s)\n", tregName(addrR), tregName(addrR));
            *outTReg = addrR;
            free(idx);
            return dupstr(tregName(addrR));
        }

        case NODE_ARRAY2D_ACCESS: {
            int base = getVarOffset(node->data.arr2d_access.name);
            if (base < 0) { fprintf(stderr, "Array2D %s undeclared\n", node->data.arr2d_access.name); exit(1); }
            int cols = getArray2DCols(node->data.arr2d_access.name);

            int rRow; char* row = genExprToTemp(node->data.arr2d_access.row, &rRow);
            int rCol; char* col = genExprToTemp(node->data.arr2d_access.col, &rCol);

            int rColsC = getNextTemp();
            fprintf(output, "  li %s, %d\n", tregName(rColsC), cols);
            fprintf(output, "  mul %s, %s, %s\n", tregName(rRow), tregName(rRow), tregName(rColsC));
            fprintf(output, "  add %s, %s, %s\n", tregName(rRow), tregName(rRow), tregName(rCol));

            int addrR = getNextTemp();
            fprintf(output, "  addi %s, $sp, %d\n", tregName(addrR), base);
            fprintf(output, "  sll %s, %s, 2\n", tregName(rRow), tregName(rRow));
            fprintf(output, "  add %s, %s, %s\n", tregName(addrR), tregName(addrR), tregName(rRow));
            fprintf(output, "  lw %s, 0(%s)\n", tregName(addrR), tregName(addrR));

            *outTReg = addrR;
            free(row); free(col);
            return dupstr(tregName(addrR));
        }

        /* --- integer or float binops --- */
/* --- integer or float binops --- */
case NODE_BINOP: {
    int lR; char* l = genExprToTemp(node->data.binop.left, &lR);
    int rR; char* r = genExprToTemp(node->data.binop.right, &rR);
    int d = getNextTemp();

    char op = node->data.binop.op;

    /* --- FLOAT BINOPS --- */
    if (node->data.binop.left->type == NODE_FLOAT ||
        node->data.binop.right->type == NODE_FLOAT) {

        switch (op) {
            case '+':
                fprintf(output, "  add.s $f%d, $f%d, $f%d\n", d, lR, rR); break;
            case '-':
                fprintf(output, "  sub.s $f%d, $f%d, $f%d\n", d, lR, rR); break;
            case '*':
                fprintf(output, "  mul.s $f%d, $f%d, $f%d\n", d, lR, rR); break;
            case '/':
                fprintf(output, "  div.s $f%d, $f%d, $f%d\n", d, lR, rR); break;

            /* float comparisons return int 0/1 result */
            case '>':
                fprintf(output, "  c.le.s $f%d, $f%d\n", rR, lR);
                fprintf(output, "  bc1t L_true_%d\n", d);
                fprintf(output, "  li %s, 0\n", tregName(d));
                fprintf(output, "  j L_end_%d\n", d);
                fprintf(output, "L_true_%d:\n", d);
                fprintf(output, "  li %s, 1\n", tregName(d));
                fprintf(output, "L_end_%d:\n", d);
                break;

            case '<':
                fprintf(output, "  c.lt.s $f%d, $f%d\n", lR, rR);
                fprintf(output, "  bc1t L_true_%d\n", d);
                fprintf(output, "  li %s, 0\n", tregName(d));
                fprintf(output, "  j L_end_%d\n", d);
                fprintf(output, "L_true_%d:\n", d);
                fprintf(output, "  li %s, 1\n", tregName(d));
                fprintf(output, "L_end_%d:\n", d);
                break;

            default:
                fprintf(stderr, "Unsupported float binop '%c'\n", op);
                exit(1);
        }

    } else {
        /* --- INTEGER BINOPS --- */
        switch (op) {
            case '+':
                fprintf(output, "  add %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                break;
            case '-':
                fprintf(output, "  sub %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                break;
            case '*':
                fprintf(output, "  mul %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                break;
            case '/':
                fprintf(output, "  div %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                break;

            /* === NEW: Relational operators === */
            case '>':  // d = (l > r)
                fprintf(output, "  sgt %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                break;
            case '<':  // d = (l < r)
                fprintf(output, "  slt %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                break;
            case 'G':  // >=
                fprintf(output, "  sge %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                break;
            case 'L':  // <=
                fprintf(output, "  sle %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                break;
            case 'E':  // ==
                fprintf(output, "  seq %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                break;
            case 'N':  // !=
                fprintf(output, "  sne %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                break;

            default:
                fprintf(stderr, "Unsupported int binop '%c'\n", op);
                exit(1);
        }
    }

    *outTReg = d;
    free(l);
    free(r);
    return dupstr(tregName(d));
}

        case NODE_FUNC_CALL: {
            int n = 0;
            const int MAXARGS = 64;
            int regs[MAXARGS];

            ASTNode* argNode = node->data.func_call.args;

            while (argNode && n < MAXARGS) {
                ASTNode* actualArgExpr = NULL;

                if (argNode->type == NODE_ARG_LIST) {
                    actualArgExpr = argNode->data.list.item;
                } else {
                    /* Single bare expr passed as args (just in case) */
                    actualArgExpr = argNode;
                }

                if (actualArgExpr) {
                    int rtmp;
                    genExprToTemp(actualArgExpr, &rtmp);
                    regs[n++] = rtmp;
                } else {
                    /* bad/malformed arg, push 0 */
                    int rtmp = getNextTemp();
                    fprintf(output, "  li %s, 0\n", tregName(rtmp));
                    regs[n++] = rtmp;
                }

                /* advance to next arg in list ONLY if this really is a NODE_ARG_LIST */
                if (argNode->type == NODE_ARG_LIST) {
                    argNode = argNode->data.list.next;
                } else {
                    break;
                }
            }

            /* spill extra args >4 on stack (right-to-left) */
            for (int i = n - 1; i >= 4; --i) {
                fprintf(output, "  addi $sp, $sp, -4\n");
                fprintf(output, "  sw %s, 0($sp)\n", tregName(regs[i]));
            }

            /* a0-a3 */
            if (n > 0) fprintf(output, "  move $a0, %s\n", tregName(regs[0]));
            if (n > 1) fprintf(output, "  move $a1, %s\n", tregName(regs[1]));
            if (n > 2) fprintf(output, "  move $a2, %s\n", tregName(regs[2]));
            if (n > 3) fprintf(output, "  move $a3, %s\n", tregName(regs[3]));

            /* call */
            fprintf(output, "  jal %s\n", node->data.func_call.name);

            /* pop stack if we pushed >4 */
            if (n > 4)
                fprintf(output, "  addi $sp, $sp, %d\n", 4 * (n - 4));

            /* get return value */
            {
                int d = getNextTemp();
                fprintf(output, "  move %s, $v0\n", tregName(d));
                *outTReg = d;
                return dupstr(tregName(d));
            }
        }


        default:
            *outTReg = getNextTemp();
            return dupstr(tregName(*outTReg));
    }
}

/* ------------------ Statements ------------------ */
static void genAssignStoreToOffset(int off, int srcReg) {
    fprintf(output, "  sw %s, %d($sp)\n", tregName(srcReg), off);
}

static void genStmt(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_DECL: {
            int off = getVarOffset(node->data.name);
            fprintf(output, "  # decl %s at %d\n", node->data.name, off);
            break;
        }
        case NODE_ARRAY_DECL: {
            int base = getVarOffset(node->data.arrdecl.name);
            fprintf(output, "  # array %s[%d] base %d\n",
                node->data.arrdecl.name, node->data.arrdecl.size, base);
            break;
        }
        case NODE_ARRAY2D_DECL: {
            int base = getVarOffset(node->data.arr2d_decl.name);
            fprintf(output, "  # array2D %s[%d][%d] base %d\n",
                node->data.arr2d_decl.name,
                node->data.arr2d_decl.rows, node->data.arr2d_decl.cols, base);
            break;
        }
        case NODE_ASSIGN: {
            int off = getVarOffset(node->data.assign.var);
            if (off < 0) { fprintf(stderr, "assign to undeclared %s\n", node->data.assign.var); exit(1); }
            int r; (void)genExprToTemp(node->data.assign.value, &r);
            genAssignStoreToOffset(off, r);
            break;
        }
        case NODE_ARRAY_ASSIGN: {
            int base = getVarOffset(node->data.arrassign.var);
            if (base < 0) { fprintf(stderr, "array undeclared %s\n", node->data.arrassign.var); exit(1); }
            int rIdx; (void)genExprToTemp(node->data.arrassign.index, &rIdx);
            int rVal; (void)genExprToTemp(node->data.arrassign.value, &rVal);
            int addr = getNextTemp();
            fprintf(output, "  addi %s, $sp, %d\n", tregName(addr), base);
            fprintf(output, "  sll %s, %s, 2\n", tregName(rIdx), tregName(rIdx));
            fprintf(output, "  add %s, %s, %s\n", tregName(addr), tregName(addr), tregName(rIdx));
            fprintf(output, "  sw %s, 0(%s)\n", tregName(rVal), tregName(addr));
            break;
        }
        case NODE_ARRAY2D_ASSIGN: {
            int base = getVarOffset(node->data.arr2d_assign.var);
            int cols = getArray2DCols(node->data.arr2d_assign.var);
            int rRow; (void)genExprToTemp(node->data.arr2d_assign.row, &rRow);
            int rCol; (void)genExprToTemp(node->data.arr2d_assign.col, &rCol);
            int rVal; (void)genExprToTemp(node->data.arr2d_assign.value, &rVal);

            int rColsC = getNextTemp();
            fprintf(output, "  li %s, %d\n", tregName(rColsC), cols);
            fprintf(output, "  mul %s, %s, %s\n", tregName(rRow), tregName(rRow), tregName(rColsC));
            fprintf(output, "  add %s, %s, %s\n", tregName(rRow), tregName(rRow), tregName(rCol));

            int addr = getNextTemp();
            fprintf(output, "  addi %s, $sp, %d\n", tregName(addr), base);
            fprintf(output, "  sll %s, %s, 2\n", tregName(rRow), tregName(rRow));
            fprintf(output, "  add %s, %s, %s\n", tregName(addr), tregName(addr), tregName(rRow));
            fprintf(output, "  sw %s, 0(%s)\n", tregName(rVal), tregName(addr));
            break;
        }
        case NODE_PRINT: {
            if (node->data.expr) {
                int r;
                genExprToTemp(node->data.expr, &r);
                fprintf(output, "  move $a0, %s\n", tregName(r));
                fprintf(output, "  li $v0, 1\n");
                fprintf(output, "  syscall\n");
            } else {
                /* Gracefully handle missing expr: just print 0 */
                int rtmp = getNextTemp();
                fprintf(output, "  li %s, 0\n", tregName(rtmp));
                fprintf(output, "  move $a0, %s\n", tregName(rtmp));
                fprintf(output, "  li $v0, 1\n");
                fprintf(output, "  syscall\n");
            }

            /* print newline either way */
            fprintf(output, "  li $v0, 11\n");
            fprintf(output, "  li $a0, 10\n");
            fprintf(output, "  syscall\n");

            break;
        }

        case NODE_RETURN: {
            if (node->data.return_expr) {
                int r; (void)genExprToTemp(node->data.return_expr, &r);
                fprintf(output, "  move $v0, %s\n", tregName(r));
            }
            /* epilogue */
            fprintf(output, "  move $sp, $fp\n");
            fprintf(output, "  lw $fp, 0($sp)\n");
            fprintf(output, "  lw $ra, 4($sp)\n");
            fprintf(output, "  addi $sp, $sp, 8\n");
            fprintf(output, "  jr $ra\n");
            break;
        }

        case NODE_STMT_LIST: {
            if (node->data.stmtlist.stmt)
                genStmt(node->data.stmtlist.stmt);

            if (node->data.stmtlist.next)
                genStmt(node->data.stmtlist.next);

            break;
        }

                /* === NEW: IF STATEMENT === */
        case NODE_IF: {
            // Generate MIPS for if (condition) then ... else ...
            char* falseLabel = (char*)malloc(32);
            char* endLabel = (char*)malloc(32);
            static int labelCount = 0;
            sprintf(falseLabel, "L_if_false_%d", labelCount);
            sprintf(endLabel,   "L_if_end_%d",   labelCount);
            labelCount++;

            // Evaluate condition
            int condReg;
            genExprToTemp(node->data.ifstmt.condition, &condReg);

            // Branch to else if condition == 0
            fprintf(output, "  beqz %s, %s\n", tregName(condReg), falseLabel);

            // THEN branch
            genStmt(node->data.ifstmt.thenBranch);

            // Jump to end after THEN
            fprintf(output, "  j %s\n", endLabel);

            // ELSE label
            fprintf(output, "%s:\n", falseLabel);

            // ELSE branch (if present)
            if (node->data.ifstmt.elseBranch)
                genStmt(node->data.ifstmt.elseBranch);

            // END label
            fprintf(output, "%s:\n", endLabel);

            free(falseLabel);
            free(endLabel);
            break;
        }


        default:
            /* function nodes are handled at top-level emitters */
            break;
    }
}

/* ------------------ Function prologue/epilogue and params copy ------------------ */

static void copyParamsIntoLocals(ASTNode* params) {
    int i = 0;
    ASTNode* p = params;

    while (p) {
        const char* name = NULL;

        if (p->type == NODE_PARAM) {
            name = p->data.param.name;
            if (!name) break;

            int off = getVarOffset(name);
            if (off < 0) {
                fprintf(stderr, "Warning: param %s has no offset (skipped)\n",
                        name ? name : "(null)");
                break;
            }

            if (i == 0)      fprintf(output, "  sw $a0, %d($sp)\n", off);
            else if (i == 1) fprintf(output, "  sw $a1, %d($sp)\n", off);
            else if (i == 2) fprintf(output, "  sw $a2, %d($sp)\n", off);
            else if (i == 3) fprintf(output, "  sw $a3, %d($sp)\n", off);
            else {
                int tmp = getNextTemp();
                int stackOff = 8 + 4 * (i - 4);
                fprintf(output, "  lw %s, %d($fp)\n", tregName(tmp), stackOff);
                fprintf(output, "  sw %s, %d($sp)\n", tregName(tmp), off);
            }

            i++;
            break;
        }

        else if (p->type == NODE_PARAM_LIST) {
            ASTNode* item = p->data.list.item;
            if (item && item->type == NODE_PARAM && item->data.param.name) {
                name = item->data.param.name;
                int off = getVarOffset(name);
                if (off < 0) {
                    fprintf(stderr, "Warning: param %s has no offset (skipped)\n",
                            name ? name : "(null)");
                    p = p->data.list.next;
                    i++;
                    continue;
                }

                if (i == 0)      fprintf(output, "  sw $a0, %d($sp)\n", off);
                else if (i == 1) fprintf(output, "  sw $a1, %d($sp)\n", off);
                else if (i == 2) fprintf(output, "  sw $a2, %d($sp)\n", off);
                else if (i == 3) fprintf(output, "  sw $a3, %d($sp)\n", off);
                else {
                    int tmp = getNextTemp();
                    int stackOff = 8 + 4 * (i - 4);
                    fprintf(output, "  lw %s, %d($fp)\n", tregName(tmp), stackOff);
                    fprintf(output, "  sw %s, %d($sp)\n", tregName(tmp), off);
                }

                i++;
            } else {
                fprintf(stderr, "Warning: skipped malformed param node in copyParamsIntoLocals\n");
            }

            p = p->data.list.next;
        }

        else {
            fprintf(stderr, "Warning: unexpected node type %d in copyParamsIntoLocals\n", p->type);
            break;
        }
    }
}


static void genFunction(ASTNode* func) {
    if (!func) return;

    const char* fname = func->data.func_decl.name ? func->data.func_decl.name : "(anon)";
    const char* rtype = func->data.func_decl.returnType ? func->data.func_decl.returnType : "int";

    // Register function in global scope for debugging / future semantic checks
    // We don't yet build paramTypes[], so pass NULL for now.
    addFunction((char*)fname, (char*)rtype, NULL, 0);

    fprintf(output, "\n.globl %s\n%s:\n", fname, fname);

    enterScope();

    // <-- FIX: only call addParams if params list exists
    int paramCount = 0;
    if (func->data.func_decl.params)
        paramCount = addParams(func->data.func_decl.params);

    (void)paramCount;
    predeclareBody(func->data.func_decl.body);

    int frame = localsBytes();

    /* save frame pointer and return address */
    fprintf(output, "  addi $sp, $sp, -8\n");
    fprintf(output, "  sw $ra, 4($sp)\n");
    fprintf(output, "  sw $fp, 0($sp)\n");
    fprintf(output, "  move $fp, $sp\n");

    if (frame > 0) fprintf(output, "  addi $sp, $sp, -%d\n", frame);

    // <-- FIX: only copy params if list exists
    if (func->data.func_decl.params)
        copyParamsIntoLocals(func->data.func_decl.params);

    genStmt(func->data.func_decl.body);

    /* implicit return for void (fall-through) */
    fprintf(output, "  move $sp, $fp\n");
    fprintf(output, "  lw $fp, 0($sp)\n");
    fprintf(output, "  lw $ra, 4($sp)\n");
    fprintf(output, "  addi $sp, $sp, 8\n");
    fprintf(output, "  jr $ra\n");

    exitScope();
}

static void genFuncList(ASTNode* list) {
    if (!list) return;
    /* list.item is a function; list.next continues */
    switch (list->type) {
        case NODE_FUNC_LIST:
            genFuncList(list->data.list.item);
            genFuncList(list->data.list.next);
            break;
        case NODE_FUNC_DECL:
            genFunction(list);
            break;
        default:
            /* allow single FUNC_DECL as program root */
            break;
    }
}

/* ------------------ Top-level ------------------ */
void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");
    if (!output) { fprintf(stderr, "Cannot open %s\n", filename); exit(1); }

    initSymTab();

    fprintf(output, ".data\n\n.text\n");

    if (root->type == NODE_FUNC_LIST) {
        /* emit all functions; ensure main is global via per-function directive above */
        genFuncList(root);
    } else if (root->type == NODE_FUNC_DECL) {
        genFunction(root);
    } else {
        /* legacy: treat as one big implicit main for older tests */
        enterScope();
        predeclareBody(root);
        int frame = localsBytes();
        fprintf(output, ".globl main\nmain:\n");
        fprintf(output, "  addi $sp, $sp, -8\n");
        fprintf(output, "  sw $ra, 4($sp)\n");
        fprintf(output, "  sw $fp, 0($sp)\n");
        fprintf(output, "  move $fp, $sp\n");
        if (frame > 0) fprintf(output, "  addi $sp, $sp, -%d\n", frame);

        genStmt(root);

        fprintf(output, "  move $sp, $fp\n");
        fprintf(output, "  lw $fp, 0($sp)\n");
        fprintf(output, "  lw $ra, 4($sp)\n");
        fprintf(output, "  addi $sp, $sp, 8\n");
        fprintf(output, "  li $v0, 10\n");
        fprintf(output, "  syscall\n");
        exitScope();
        fclose(output);
        return;
    }

    fclose(output);
}
