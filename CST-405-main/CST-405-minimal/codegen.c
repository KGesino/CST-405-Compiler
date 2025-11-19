#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"

static FILE* output;
static int tempReg = 0;

static const char* currentFunctionName = NULL;


/* ---------------- Helpers ---------------- */
static int getNextTemp() {
    int reg = tempReg++;
    if (tempReg > 17) tempReg = 0;  // use $t0–$t9, then $s0–$s7
    return reg;
}


static int getArray2DCols(const char* name) {
    int rows, cols;
    getArray2DSizes(name, &rows, &cols);
    return cols;
}

static const char* tregName(int r) {
    static const char* names[] = {
        "$t0", "$t1", "$t2", "$t3", "$t4",
        "$t5", "$t6", "$t7", "$t8", "$t9",
        "$s0", "$s1", "$s2", "$s3",
        "$s4", "$s5", "$s6", "$s7"
    };

    if (r >= 0 && r < (int)(sizeof(names)/sizeof(names[0])))
        return names[r];
    return "$t9";  // fallback
}

static const char* fregName(int r) {
    // if you're just using f0, f1, ... up to some max, you can either:
    // 1) also use a table, or
    // 2) generate on the fly but return different strings.
    // simplest: small table for f0–f15, etc.
    static const char* fnames[] = {
        "$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$f6", "$f7",
        "$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15"
    };

    if (r >= 0 && r < (int)(sizeof(fnames)/sizeof(fnames[0])))
        return fnames[r];
    return "$f0";
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
            fprintf(output, "  li %s, %d\n", tregName(r), node->data.boolval ? 1 : 0);
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
        case NODE_CHAR: {
            int r = getNextTemp();
            fprintf(output, "  li %s, %d\n", tregName(r), (int)node->data.ch);
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

        case NODE_UNOP: {
            char* expr = genExprToTemp(node->data.unop.expr, outTReg);
            if (node->data.unop.op == '!') {
                fprintf(output, "  seq %s, %s, $zero\n", tregName(*outTReg), expr);
            }
            return dupstr(tregName(*outTReg));
        }

        /* ============================================================
         * BINARY OPERATIONS
         * ============================================================ */
        case NODE_BINOP: {
            /* --- Preserve current tempReg to avoid overwriting --- */
            int savedTemp = tempReg;

            /* Generate left operand */
            int lR; 
            char* l = genExprToTemp(node->data.binop.left, &lR);

            /* Generate right operand */
            int rR; 
            char* r = genExprToTemp(node->data.binop.right, &rR);

            /* Bump tempReg so result gets a fresh register */
            tempReg = (lR > rR ? lR : rR) + 1;


            int d = getNextTemp();
            char op = node->data.binop.op;

            int leftIsFloat  = (node->data.binop.left->type  == NODE_FLOAT);
            int rightIsFloat = (node->data.binop.right->type == NODE_FLOAT);
            int isFloat = leftIsFloat || rightIsFloat;

            /* ============================================================
            * BINARY OPERATION CODEGEN — UPDATED WITH FLOAT COMPARISONS
            * ============================================================ */
            if (isFloat) {
                /* ---------------- FLOAT ARITHMETIC ---------------- */
                switch (op) {
                    case '+':
                        fprintf(output, "  add.s %s, %s, %s\n",
                                fregName(d), fregName(lR), fregName(rR));
                        break;

                    case '-':
                        fprintf(output, "  sub.s %s, %s, %s\n",
                                fregName(d), fregName(lR), fregName(rR));
                        break;

                    case '*':
                        fprintf(output, "  mul.s %s, %s, %s\n",
                                fregName(d), fregName(lR), fregName(rR));
                        break;

                    case '/':
                        fprintf(output, "  div.s %s, %s, %s\n",
                                fregName(d), fregName(lR), fregName(rR));
                        break;

                    /* ---------------- FLOAT COMPARISONS ---------------- */
                    case '>':     /* left > right */
                        fprintf(output,
                            "  c.le.s %s, %s\n"           /* if left <= right => false */
                            "  bc1t _cmp_false_%d\n"
                            "  li %s, 1\n"                /* true */
                            "  j _cmp_end_%d\n"
                            "_cmp_false_%d:\n"
                            "  li %s, 0\n"
                            "_cmp_end_%d:\n",
                            fregName(lR), fregName(rR),
                            d,
                            tregName(d), d,
                            d,
                            tregName(d),
                            d);
                        break;

                    case '<':     /* left < right */
                        fprintf(output,
                            "  c.lt.s %s, %s\n"           /* if left < right => true */
                            "  bc1t _cmp_true_%d\n"
                            "  li %s, 0\n"                /* false */
                            "  j _cmp_end_%d\n"
                            "_cmp_true_%d:\n"
                            "  li %s, 1\n"                /* true */
                            "_cmp_end_%d:\n",
                            fregName(lR), fregName(rR),
                            d,
                            tregName(d), d,
                            d,
                            tregName(d),
                            d);
                        break;

                    case 'E':     /* left == right */
                        fprintf(output,
                            "  c.eq.s %s, %s\n"
                            "  bc1t _cmp_true_%d\n"
                            "  li %s, 0\n"
                            "  j _cmp_end_%d\n"
                            "_cmp_true_%d:\n"
                            "  li %s, 1\n"
                            "_cmp_end_%d:\n",
                            fregName(lR), fregName(rR),
                            d,
                            tregName(d), d,
                            d,
                            tregName(d),
                            d);
                        break;

                    case 'N':     /* left != right */
                        fprintf(output,
                            "  c.eq.s %s, %s\n"
                            "  bc1f _cmp_true_%d\n"       /* if NOT equal → true */
                            "  li %s, 0\n"                /* false */
                            "  j _cmp_end_%d\n"
                            "_cmp_true_%d:\n"
                            "  li %s, 1\n"                /* true */
                            "_cmp_end_%d:\n",
                            fregName(lR), fregName(rR),
                            d,
                            tregName(d), d,
                            d,
                            tregName(d),
                            d);
                        break;

                    default:
                        fprintf(stderr, "Unsupported float binop '%c'\n", op);
                        exit(1);
                }

            } else {

                /* ---------------- INTEGER OPS (UNCHANGED) ---------------- */
                switch (op) {
                    case '+': fprintf(output, "  add %s, %s, %s\n",
                                    tregName(d), tregName(lR), tregName(rR)); break;
                    case '-': fprintf(output, "  sub %s, %s, %s\n",
                                    tregName(d), tregName(lR), tregName(rR)); break;
                    case '*': fprintf(output, "  mul %s, %s, %s\n",
                                    tregName(d), tregName(lR), tregName(rR)); break;
                    case '/': fprintf(output, "  div %s, %s, %s\n",
                                    tregName(d), tregName(lR), tregName(rR)); break;

                    case '>': fprintf(output, "  sgt %s, %s, %s\n",
                                    tregName(d), tregName(lR), tregName(rR)); break;
                    case '<': fprintf(output, "  slt %s, %s, %s\n",
                                    tregName(d), tregName(lR), tregName(rR)); break;
                    case 'E': fprintf(output, "  seq %s, %s, %s\n",
                                    tregName(d), tregName(lR), tregName(rR)); break;
                    case 'N': fprintf(output, "  sne %s, %s, %s\n",
                                    tregName(d), tregName(lR), tregName(rR)); break;

                    case '&':
                        fprintf(output, "  sne %s, %s, $zero\n", tregName(lR), tregName(lR));
                        fprintf(output, "  sne %s, %s, $zero\n", tregName(rR), tregName(rR));
                        fprintf(output, "  and %s, %s, %s\n",
                                tregName(d), tregName(lR), tregName(rR));
                        break;

                    case '|':
                        fprintf(output, "  or %s, %s, %s\n",
                                tregName(d), tregName(lR), tregName(rR));
                        fprintf(output, "  sne %s, %s, $zero\n",
                                tregName(d), tregName(d));
                        break;

                    default:
                        fprintf(stderr, "Unsupported int/binop '%c'\n", op);
                        exit(1);
                }
            }

            /* ---------------- Return result ---------------- */
            *outTReg = d;
            free(l);
            free(r);
            return dupstr(isFloat ? fregName(d) : tregName(d));

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

        case NODE_SWAP: {
            const char* a = node->data.swap.left;
            const char* b = node->data.swap.right;

            int offA = getVarOffset(a);
            int offB = getVarOffset(b);

            if (offA < 0 || offB < 0) {
                fprintf(stderr, "swap of undeclared vars %s, %s\n", a, b);
                exit(1);
            }

            int r1 = getNextTemp();   // temp register for a
            int r2 = getNextTemp();   // temp register for b

            fprintf(output, "  # swap %s <-> %s\n", a, b);

            fprintf(output, "  lw %s, %d($sp)\n", tregName(r1), offA);
            fprintf(output, "  lw %s, %d($sp)\n", tregName(r2), offB);

            fprintf(output, "  sw %s, %d($sp)\n", tregName(r2), offA);
            fprintf(output, "  sw %s, %d($sp)\n", tregName(r1), offB);

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
        
        /* ----------------------------------------------
         * WRITE (no newline)
         * ---------------------------------------------- */
        case NODE_WRITE: {
            if (node->data.expr) {
                int r;
                genExprToTemp(node->data.expr, &r);

                switch(node->data.expr->type) {
                    case NODE_CHAR:
                        fprintf(output, "  li $v0, 11\n");
                        fprintf(output, "  move $a0, %s\n", tregName(r));
                        break;

                    case NODE_FLOAT:
                        fprintf(output, "  li $v0, 2\n");
                        fprintf(output, "  mov.s $f12, %s\n", fregName(r));
                        break;

                    default:  // int / bool
                        fprintf(output, "  li $v0, 1\n");
                        fprintf(output, "  move $a0, %s\n", tregName(r));
                        break;
                }

                fprintf(output, "  syscall\n");
            }
            break;
        }


        /* ----------------------------------------------
         * WRITELN (newline only)
         * ---------------------------------------------- */
        case NODE_WRITELN: {
            fprintf(output, "  li $v0, 11\n");
            fprintf(output, "  li $a0, 10\n");
            fprintf(output, "  syscall\n");
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

        case NODE_WHILE: {
            static int wlabel = 0;
            char Lstart[32], Lend[32];
            sprintf(Lstart, "L_while_start_%d", wlabel);
            sprintf(Lend, "L_while_end_%d", wlabel++);
            
            fprintf(output, "%s:\n", Lstart);
            int condReg;
            genExprToTemp(node->data.whilestmt.condition, &condReg);
            fprintf(output, "  beqz %s, %s\n", tregName(condReg), Lend);
            genStmt(node->data.whilestmt.body);
            fprintf(output, "  j %s\n%s:\n", Lstart, Lend);
            break;
        }


                /* ============================================================
         * NEW: Parallel Choice ("race { ... | ... } first_wins")
         * ============================================================ */
        case NODE_RACE: {
            static int raceLabel = 0;
            char Lleft[32], Lright[32], Lend[32];
            sprintf(Lleft,  "L_race_left_%d",  raceLabel);
            sprintf(Lright, "L_race_right_%d", raceLabel);
            sprintf(Lend,   "L_race_end_%d",   raceLabel++);
            
            fprintf(output, "\n  # --- Begin race block ---\n");
            fprintf(output, "  # Strategy: first_wins\n");
            fprintf(output, "  li $t7, 0        # race_flag = 0\n");
            fprintf(output, "  j %s\n", Lleft);

            /* === Left Branch === */
            fprintf(output, "%s:\n", Lleft);
            genStmt(node->data.racestmt.left);
            fprintf(output, "  beqz $t7, %s\n", Lend);   // if no winner yet, mark win
            fprintf(output, "  j %s\n", Lright);          // if already won, skip right

            /* === Right Branch === */
            fprintf(output, "%s:\n", Lright);
            genStmt(node->data.racestmt.right);
            fprintf(output, "  beqz $t7, %s\n", Lend);   // mark win if still free
            fprintf(output, "  j %s\n", Lend);           // both done

            /* === End of race === */
            fprintf(output, "%s:\n", Lend);
            fprintf(output, "  li $t7, 1        # first branch won\n");
            fprintf(output, "  # --- End race block ---\n\n");
            break;
        }


        case NODE_RETURN: {
            if (node->data.return_expr) {
                int r; genExprToTemp(node->data.return_expr, &r);
                fprintf(output, "  move $v0, %s\n", tregName(r));
            }
            fprintf(output, "  j %s_epilogue\n", currentFunctionName);
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
    tempReg = 0;
    const char* fname = func->data.func_decl.name;
    currentFunctionName = fname;
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
    fprintf(output, "%s_epilogue:\n", fname);
    fprintf(output,
        "  move $sp, $fp\n"
        "  lw $fp, 0($sp)\n"
        "  lw $ra, 4($sp)\n"
        "  addi $sp, $sp, 8\n"
        "  jr $ra\n"
    );
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
    fprintf(output,
    ".data\n\n"
    ".text\n"
    ".globl _start\n"
    "_start:\n"
    "  jal main\n"
    "  li $v0, 10\n"
    "  syscall\n\n"
    );

    if (root->type == NODE_FUNC_LIST)
        genFuncList(root);
    else if (root->type == NODE_FUNC_DECL)
        genFunction(root);
    fclose(output);
}
