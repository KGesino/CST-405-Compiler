#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"

static FILE* output;
static int tempReg = 0;

/* ---------------- Helpers ---------------- */
static int getNextTemp() {
    int reg = tempReg++;
    if (tempReg > 7) tempReg = 0;  // reuse $t0-$t7
    return reg;
}

static int getArray2DCols(const char* name) {
    int rows, cols;
    getArray2DSizes(name, &rows, &cols);
    return cols;
}

static const char* tregName(int r) {
    static char buf[8];
    snprintf(buf, sizeof(buf), "$t%d", r);
    return buf;
}

static const char* fregName(int r) {
    static char buf[8];
    snprintf(buf, sizeof(buf), "$f%d", r);
    return buf;
}

static char* dupstr(const char* s) {
    char* r = malloc(strlen(s) + 1);
    strcpy(r, s);
    return r;
}

/* forward decls */
static void genStmt(ASTNode* node);
static char* genExprToTemp(ASTNode* node, int* outTReg);
static void genFunction(ASTNode* func);
static void genFuncList(ASTNode* list);

/* ---------------- Scope helpers ---------------- */
static void predeclareBody(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case NODE_DECL:
            addVar(node->data.name, "int");
            break;
        case NODE_ARRAY_DECL:
            addArray(node->data.arrdecl.name, "int", node->data.arrdecl.size);
            break;
        case NODE_ARRAY2D_DECL:
            addArray2D(node->data.arr2d_decl.name, "int",
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

static int addParams(ASTNode* params) {
    int count = 0;
    ASTNode* p = params;
    while (p) {
        if (p->type == NODE_PARAM) {
            addParameter(p->data.param.name, p->data.param.type);
            count++;
            break;
        } else if (p->type == NODE_PARAM_LIST) {
            ASTNode* item = p->data.list.item;
            if (item && item->type == NODE_PARAM) {
                addParameter(item->data.param.name, item->data.param.type);
                count++;
            }
            p = p->data.list.next;
        } else break;
    }
    return count;
}

static int localsBytes() {
    int n = getTotalStackBytes();
    return (n < 0) ? 0 : n;
}

/* ---------------- Expressions ---------------- */
static char* genExprToTemp(ASTNode* node, int* outTReg) {
    if (!node) {
        int r = getNextTemp();
        *outTReg = r;
        fprintf(output, "  li %s, 0\n", tregName(r));
        return dupstr(tregName(r));
    }

    switch (node->type) {
        case NODE_NUM: {
            int r = getNextTemp();
            fprintf(output, "  li %s, %d\n", tregName(r), node->data.num);
            *outTReg = r;
            return dupstr(tregName(r));
        }

        case NODE_BOOL: {
            int r = getNextTemp();
            fprintf(output, "  li %s, %d\n", tregName(r), node->data.num ? 1 : 0);
            *outTReg = r;
            return dupstr(tregName(r));
        }

        case NODE_FLOAT: {
            static int lbl = 0;
            int f = getNextTemp();
            fprintf(output, "  .data\nL_fconst_%d: .float %f\n.text\n", lbl, node->data.fnum);
            fprintf(output, "  l.s %s, L_fconst_%d\n", fregName(f), lbl++);
            *outTReg = f;
            return dupstr(fregName(f));
        }

        case NODE_VAR: {
            int off = getVarOffset(node->data.name);
            if (off < 0) { fprintf(stderr, "Var %s undeclared\n", node->data.name); exit(1); }
            int r = getNextTemp();
            fprintf(output, "  lw %s, %d($sp)\n", tregName(r), off);
            *outTReg = r;
            return dupstr(tregName(r));
        }

        case NODE_UNOP: {
            char* expr = genExprToTemp(node->data.unop.expr, outTReg);
            if (node->data.unop.op == '!') {
                fprintf(output, "  seq %s, %s, $zero\n", tregName(*outTReg), expr);
            }
            return dupstr(tregName(*outTReg));
        }

        case NODE_BINOP: {
            int lR; char* l = genExprToTemp(node->data.binop.left, &lR);
            int rR; char* r = genExprToTemp(node->data.binop.right, &rR);
            int d = getNextTemp();
            char op = node->data.binop.op;

            int leftIsFloat  = (node->data.binop.left->type  == NODE_FLOAT);
            int rightIsFloat = (node->data.binop.right->type == NODE_FLOAT);
            int isFloat = leftIsFloat || rightIsFloat;

            if (isFloat) {
                switch (op) {
                    /* ===== Float Arithmetic ===== */
                    case '+': fprintf(output, "  add.s %s, %s, %s\n", fregName(d), fregName(lR), fregName(rR)); break;
                    case '-': fprintf(output, "  sub.s %s, %s, %s\n", fregName(d), fregName(lR), fregName(rR)); break;
                    case '*': fprintf(output, "  mul.s %s, %s, %s\n", fregName(d), fregName(lR), fregName(rR)); break;
                    case '/': fprintf(output, "  div.s %s, %s, %s\n", fregName(d), fregName(lR), fregName(rR)); break;

                    /* ===== Float Comparisons ===== */
                    case '>':
                    case '<':
                    case 'E':
                    case 'N':
                    case 'G':
                    case 'L': {
                        static int lbl = 0;
                        int iReg = getNextTemp();

                        switch (op) {
                            case '>': fprintf(output, "  c.lt.s %s, %s\n", fregName(rR), fregName(lR)); break;
                            case '<': fprintf(output, "  c.lt.s %s, %s\n", fregName(lR), fregName(rR)); break;
                            case 'E': fprintf(output, "  c.eq.s %s, %s\n", fregName(lR), fregName(rR)); break;
                            case 'N': fprintf(output, "  c.eq.s %s, %s\n", fregName(lR), fregName(rR)); break;
                            case 'G': fprintf(output, "  c.le.s %s, %s\n", fregName(rR), fregName(lR)); break;
                            case 'L': fprintf(output, "  c.le.s %s, %s\n", fregName(lR), fregName(rR)); break;
                        }

                        if (op == 'N') {
                            fprintf(output, "  li %s, 1\n", tregName(iReg));
                            fprintf(output, "  bc1t L_false_%d\n", lbl);
                            fprintf(output, "  li %s, 0\n", tregName(iReg));
                            fprintf(output, "L_false_%d:\n", lbl++);
                        } else {
                            fprintf(output, "  li %s, 0\n", tregName(iReg));
                            fprintf(output, "  bc1f L_false_%d\n", lbl);
                            fprintf(output, "  li %s, 1\n", tregName(iReg));
                            fprintf(output, "L_false_%d:\n", lbl++);
                        }

                        d = iReg;
                        break;
                    }

                    default:
                        fprintf(stderr, "Unsupported float binop '%c'\n", op);
                        exit(1);
                }
            } else {
                switch (op) {
                    case '+': fprintf(output, "  add %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR)); break;
                    case '-': fprintf(output, "  sub %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR)); break;
                    case '*': fprintf(output, "  mul %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR)); break;
                    case '/': fprintf(output, "  div %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR)); break;

                    case '>': fprintf(output, "  sgt %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR)); break;
                    case '<': fprintf(output, "  slt %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR)); break;
                    case 'E': fprintf(output, "  seq %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR)); break;
                    case 'N': fprintf(output, "  sne %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR)); break;

                    /* === NEW BOOLEAN OPS === */
                    case '&':  // logical AND
                        fprintf(output, "  sne %s, %s, $zero\n", tregName(lR), tregName(lR));
                        fprintf(output, "  sne %s, %s, $zero\n", tregName(rR), tregName(rR));
                        fprintf(output, "  and %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                        break;

                    case '|':  // logical OR
                        fprintf(output, "  or %s, %s, %s\n", tregName(d), tregName(lR), tregName(rR));
                        fprintf(output, "  sne %s, %s, $zero\n", tregName(d), tregName(d));
                        break;

                    default:
                        fprintf(stderr, "Unsupported int/binop '%c'\n", op);
                        exit(1);
                }
            }

            *outTReg = d;
            free(l);
            free(r);
            return dupstr(isFloat ? tregName(d) : tregName(d));
        }

        default: {
            int r = getNextTemp();
            *outTReg = r;
            fprintf(output, "  li %s, 0\n", tregName(r));
            return dupstr(tregName(r));
        }
    }
}


/* ---------------- Statements ---------------- */
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

        case NODE_ASSIGN: {
            int off = getVarOffset(node->data.assign.var);
            if (off < 0) { fprintf(stderr, "assign to undeclared %s\n", node->data.assign.var); exit(1); }
            int r; genExprToTemp(node->data.assign.value, &r);
            genAssignStoreToOffset(off, r);
            break;
        }

        case NODE_PRINT: {
            if (node->data.expr) {
                int r;
                genExprToTemp(node->data.expr, &r);
                if (node->data.expr->type == NODE_FLOAT) {
                    fprintf(output, "  mov.s $f12, $f%d\n", r);
                    fprintf(output, "  li $v0, 2\n");
                } else {
                    fprintf(output, "  move $a0, %s\n", tregName(r));
                    fprintf(output, "  li $v0, 1\n");
                }
                fprintf(output, "  syscall\n");
            }
            fprintf(output, "  li $v0, 11\n  li $a0, 10\n  syscall\n");
            break;
        }

        case NODE_IF: {
            static int label = 0;
            char Lfalse[32], Lend[32];
            sprintf(Lfalse, "L_if_false_%d", label);
            sprintf(Lend, "L_if_end_%d", label++);
            int cond;
            genExprToTemp(node->data.ifstmt.condition, &cond);
            fprintf(output, "  beqz %s, %s\n", tregName(cond), Lfalse);
            genStmt(node->data.ifstmt.thenBranch);
            fprintf(output, "  j %s\n%s:\n", Lend, Lfalse);
            if (node->data.ifstmt.elseBranch)
                genStmt(node->data.ifstmt.elseBranch);
            fprintf(output, "%s:\n", Lend);
            break;
        }

        case NODE_RETURN: {
            if (node->data.return_expr) {
                int r; genExprToTemp(node->data.return_expr, &r);
                fprintf(output, "  move $v0, %s\n", tregName(r));
            }
            fprintf(output, "  move $sp, $fp\n  lw $fp, 0($sp)\n  lw $ra, 4($sp)\n  addi $sp, $sp, 8\n  jr $ra\n");
            break;
        }

        case NODE_STMT_LIST: {
            genStmt(node->data.stmtlist.stmt);
            genStmt(node->data.stmtlist.next);
            break;
        }

        default: break;
    }
}

/* ---------------- Functions ---------------- */
static void copyParamsIntoLocals(ASTNode* params) {
    int i = 0;
    ASTNode* p = params;
    while (p) {
        const char* name = NULL;
        if (p->type == NODE_PARAM) {
            name = p->data.param.name;
            if (!name) break;
            int off = getVarOffset(name);
            if (i == 0) fprintf(output, "  sw $a0, %d($sp)\n", off);
            else if (i == 1) fprintf(output, "  sw $a1, %d($sp)\n", off);
            else if (i == 2) fprintf(output, "  sw $a2, %d($sp)\n", off);
            else if (i == 3) fprintf(output, "  sw $a3, %d($sp)\n", off);
            i++;
            break;
        } else if (p->type == NODE_PARAM_LIST) {
            ASTNode* item = p->data.list.item;
            if (item && item->type == NODE_PARAM)
                name = item->data.param.name;
            if (!name) { p = p->data.list.next; continue; }
            int off = getVarOffset(name);
            if (i == 0) fprintf(output, "  sw $a0, %d($sp)\n", off);
            else if (i == 1) fprintf(output, "  sw $a1, %d($sp)\n", off);
            else if (i == 2) fprintf(output, "  sw $a2, %d($sp)\n", off);
            else if (i == 3) fprintf(output, "  sw $a3, %d($sp)\n", off);
            i++;
            p = p->data.list.next;
        } else break;
    }
}

static void genFunction(ASTNode* func) {
    const char* fname = func->data.func_decl.name;
    const char* rtype = func->data.func_decl.returnType;
    addFunction((char*)fname, (char*)rtype, NULL, 0);
    fprintf(output, "\n.globl %s\n%s:\n", fname, fname);
    enterScope();
    if (func->data.func_decl.params)
        addParams(func->data.func_decl.params);
    predeclareBody(func->data.func_decl.body);
    int frame = localsBytes();
    fprintf(output, "  addi $sp, $sp, -8\n  sw $ra, 4($sp)\n  sw $fp, 0($sp)\n  move $fp, $sp\n");
    if (frame > 0) fprintf(output, "  addi $sp, $sp, -%d\n", frame);
    if (func->data.func_decl.params)
        copyParamsIntoLocals(func->data.func_decl.params);
    genStmt(func->data.func_decl.body);
    fprintf(output, "  move $sp, $fp\n  lw $fp, 0($sp)\n  lw $ra, 4($sp)\n  addi $sp, $sp, 8\n  jr $ra\n");
    exitScope();
}

static void genFuncList(ASTNode* list) {
    if (!list) return;
    if (list->type == NODE_FUNC_LIST) {
        genFuncList(list->data.list.item);
        genFuncList(list->data.list.next);
    } else if (list->type == NODE_FUNC_DECL)
        genFunction(list);
}

/* ---------------- Entry ---------------- */
void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");
    if (!output) { fprintf(stderr, "Cannot open %s\n", filename); exit(1); }
    initSymTab();
    fprintf(output, ".data\n\n.text\n");
    if (root->type == NODE_FUNC_LIST)
        genFuncList(root);
    else if (root->type == NODE_FUNC_DECL)
        genFunction(root);
    fclose(output);
}
