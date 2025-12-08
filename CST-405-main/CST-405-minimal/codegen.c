#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "codegen.h"
#include "symtab.h"

static FILE* output;

/* current function info */
static const char* currentFunctionName = NULL;
static const char* currentFunctionReturnType = NULL; /* "int", "float", ... */

/* ============================================================
 * TEMP REGISTERS
 * ============================================================ */

/* int temps: 0..17 -> $t0..$t9,$s0..$s7 */
static int nextIntTemp = 0;
/* float temps: 0..15 -> $f0..$f15 */
static int nextFloatTemp = 0;

static const char* tregName(int r) {
    static const char* names[] = {
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$t8", "$t9", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5",
        "$s6", "$s7"
    };
    if (r >= 0 && r < (int)(sizeof(names) / sizeof(names[0])))
        return names[r];
    return "$t9"; /* fallback */
}

static const char* fregName(int r) {
    static const char* fnames[] = {
        "$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$f6", "$f7",
        "$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15"
    };
    if (r >= 0 && r < (int)(sizeof(fnames) / sizeof(fnames[0])))
        return fnames[r];
    return "$f0";
}

static int getNextIntTemp() {
    int r = nextIntTemp++;
    if (nextIntTemp > 17) nextIntTemp = 0;
    return r;
}

static int getNextFloatTemp() {
    int r = nextFloatTemp++;
    if (nextFloatTemp > 15) nextFloatTemp = 0;
    return r;
}

/* ============================================================
 * TYPE HELPERS
 * ============================================================ */

extern const char* inferExprType(ASTNode* expr);  /* from symtab.c */

static int isFloatTypeStr(const char* t)  { return t && strcmp(t, "float") == 0; }
static int isIntLikeTypeStr(const char* t){ return t && (strcmp(t, "int") == 0 ||
                                                          strcmp(t, "bool") == 0 ||
                                                          strcmp(t, "char") == 0); }

typedef enum {
    VAL_INT,   /* int / bool / char in a GP register */
    VAL_FLOAT  /* float in an FP register */
} ValueKind;

typedef struct {
    ValueKind kind;
    int       reg;  /* index into tregName() or fregName(), depending on kind */
} Value;

/* promote int-like value to float */
static Value promoteToFloat(Value v) {
    if (v.kind == VAL_FLOAT) return v;

    int f = getNextFloatTemp();
    fprintf(output, " mtc1 %s, %s\n", tregName(v.reg), fregName(f));
    fprintf(output, " cvt.s.w %s, %s\n", fregName(f), fregName(f));

    Value out = { VAL_FLOAT, f };
    return out;
}

/* convert float value to int (used in conditions etc.) */
static Value floatToInt(Value v) {
    if (v.kind == VAL_INT) return v;

    int t = getNextIntTemp();
    fprintf(output, " cvt.w.s %s, %s\n", fregName(v.reg), fregName(v.reg));
    fprintf(output, " mfc1 %s, %s\n", tregName(t), fregName(v.reg));

    Value out = { VAL_INT, t };
    return out;
}

/* ============================================================
 * SCOPE HELPERS
 * ============================================================ */

static void predeclareBody(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_DECL:
            /* NOTE: currently treats all simple decls as int.
             * If you add typed decl AST nodes, call addVar with real type. */
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
            addParameter(p->data.param.name, p->data.param.type, p->data.param.isArray);
            count++;
        }
        else if (p->type == NODE_ARRAY_DECL) {
            addParameter(p->data.arrdecl.name, "int", 1);
            count++;
        }
        else if (p->type == NODE_PARAM_LIST) {
            ASTNode* item = p->data.list.item;
            if (item) {
                if (item->type == NODE_PARAM)
                    addParameter(item->data.param.name, item->data.param.type, item->data.param.isArray);
                else if (item->type == NODE_ARRAY_DECL)
                    addParameter(item->data.arrdecl.name, "int", 1);
                count++;
            }
            p = p->data.list.next;
            continue;
        }

        p = p->data.list.next;
    }

    return count;
}

static int localsBytes() {
    int n = getTotalStackBytes();
    return (n < 0) ? 0 : n;
}

/* ============================================================
 * EXPRESSIONS
 * ============================================================ */

static Value genExpr(ASTNode* node);

/* generate float literal as data + load */
static Value genFloatLiteral(float fval) {
    static int flabel = 0;
    int f = getNextFloatTemp();

    fprintf(output,
            " .data\n"
            "L_fconst_%d: .float %f\n"
            ".text\n",
            flabel, fval);

    fprintf(output, " l.s %s, L_fconst_%d\n", fregName(f), flabel++);
    Value v = { VAL_FLOAT, f };
    return v;
}

static Value genExpr(ASTNode* node) {
    if (!node) {
        int r = getNextIntTemp();
        fprintf(output, " li %s, 0\n", tregName(r));
        Value v = { VAL_INT, r };
        return v;
    }

    switch (node->type) {

        /* ---------------- LITERALS ---------------- */
        case NODE_NUM: {
            int r = getNextIntTemp();
            fprintf(output, " li %s, %d\n", tregName(r), node->data.num);
            Value v = { VAL_INT, r };
            return v;
        }

        case NODE_FLOAT:
            return genFloatLiteral(node->data.fnum);

        case NODE_BOOL: {
            int r = getNextIntTemp();
            fprintf(output, " li %s, %d\n", tregName(r),
                    node->data.boolval ? 1 : 0);
            Value v = { VAL_INT, r };
            return v;
        }

        case NODE_CHAR: {
            int r = getNextIntTemp();
            fprintf(output, " li %s, %d\n", tregName(r), (int)node->data.ch);
            Value v = { VAL_INT, r };
            return v;
        }

        /* ---------------- VARIABLE ---------------- */
        case NODE_VAR: {
            const char* t = inferExprType(node); /* uses symtab */
            int off = getVarOffset(node->data.name);
            if (off < 0) {
                fprintf(stderr, "Var %s undeclared\n", node->data.name);
                exit(1);
            }

            if (isFloatTypeStr(t)) {
                int f = getNextFloatTemp();
                fprintf(output, " l.s %s, %d($sp)\n", fregName(f), off);
                Value v = { VAL_FLOAT, f };
                return v;
            } else {
                int r = getNextIntTemp();
                fprintf(output, " lw %s, %d($sp)\n", tregName(r), off);
                Value v = { VAL_INT, r };
                return v;
            }
        }

        /* ---------------- UNARY ---------------- */
        case NODE_UNOP: {
            Value v = genExpr(node->data.unop.expr);

            if (node->data.unop.op == '!') {
                /* logical not → int */
                if (v.kind == VAL_FLOAT)
                    v = floatToInt(v);

                int d = getNextIntTemp();
                fprintf(output, " seq %s, %s, $zero\n",
                        tregName(d), tregName(v.reg));
                Value out = { VAL_INT, d };
                return out;
            }
            else if (node->data.unop.op == '-') {
                /* unary minus: keep kind */
                if (v.kind == VAL_FLOAT) {
                    int d = getNextFloatTemp();
                    fprintf(output, " neg.s %s, %s\n",
                            fregName(d), fregName(v.reg));
                    Value out = { VAL_FLOAT, d };
                    return out;
                } else {
                    int d = getNextIntTemp();
                    fprintf(output, " sub %s, $zero, %s\n",
                            tregName(d), tregName(v.reg));
                    Value out = { VAL_INT, d };
                    return out;
                }
            }

            /* default: just pass through */
            return v;
        }

        /* ---------------- BINARY ---------------- */
        case NODE_BINOP: {
            char op = node->data.binop.op;

            const char* leftType  = inferExprType(node->data.binop.left);
            const char* rightType = inferExprType(node->data.binop.right);
            const char* resType   = inferExprType(node);

            int resIsFloat = isFloatTypeStr(resType);
            int resIsBool  = (resType && strcmp(resType, "bool") == 0);

            Value L = genExpr(node->data.binop.left);
            Value R = genExpr(node->data.binop.right);

            /* ------ arithmetic (+, -, *, /) ------ */
            if (op == '+' || op == '-' || op == '*' || op == '/') {
                if (resIsFloat) {
                    /* promote both to float */
                    L = promoteToFloat(L);
                    R = promoteToFloat(R);

                    int d = getNextFloatTemp();
                    switch (op) {
                        case '+':
                            fprintf(output, " add.s %s, %s, %s\n",
                                    fregName(d), fregName(L.reg), fregName(R.reg));
                            break;
                        case '-':
                            fprintf(output, " sub.s %s, %s, %s\n",
                                    fregName(d), fregName(L.reg), fregName(R.reg));
                            break;
                        case '*':
                            fprintf(output, " mul.s %s, %s, %s\n",
                                    fregName(d), fregName(L.reg), fregName(R.reg));
                            break;
                        case '/':
                            fprintf(output, " div.s %s, %s, %s\n",
                                    fregName(d), fregName(L.reg), fregName(R.reg));
                            break;
                    }
                    Value out = { VAL_FLOAT, d };
                    return out;
                } else {
                    /* int-like arithmetic */
                    if (L.kind == VAL_FLOAT) L = floatToInt(L);
                    if (R.kind == VAL_FLOAT) R = floatToInt(R);

                    int d = getNextIntTemp();
                    switch (op) {
                        case '+':
                            fprintf(output, " add %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            break;
                        case '-':
                            fprintf(output, " sub %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            break;
                        case '*':
                            fprintf(output, " mul %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            break;
                        case '/':
                            fprintf(output, " div %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            break;
                    }
                    Value out = { VAL_INT, d };
                    return out;
                }
            }

            /* ------ comparisons & logical ops ------ */
            if (resIsBool) {
                /* result will be int 0/1 */
                static int cmpLabel = 0;
                int id = cmpLabel++;

                /* float comparisons if either operand is float */
                int useFloatCmp = isFloatTypeStr(leftType) ||
                                  isFloatTypeStr(rightType) ||
                                  L.kind == VAL_FLOAT ||
                                  R.kind == VAL_FLOAT;

                if (useFloatCmp) {
                    L = promoteToFloat(L);
                    R = promoteToFloat(R);
                    int d = getNextIntTemp();

                    char Lfalse[32], Ltrue[32], Lend[32];
                    sprintf(Lfalse, "_cmp_false_%d", id);
                    sprintf(Ltrue,  "_cmp_true_%d", id);
                    sprintf(Lend,   "_cmp_end_%d",  id);

                    switch (op) {
                        case '>':
                            /* L > R  ≡ !(L <= R) */
                            fprintf(output,
                                " c.le.s %s, %s\n"
                                " bc1t %s\n"
                                " li %s, 1\n"
                                " j %s\n"
                                "%s:\n"
                                " li %s, 0\n"
                                "%s:\n",
                                fregName(L.reg), fregName(R.reg),
                                Lfalse,
                                tregName(d),
                                Lend,
                                Lfalse,
                                tregName(d),
                                Lend);
                            break;

                        case '<':
                            fprintf(output,
                                " c.lt.s %s, %s\n"
                                " bc1t %s\n"
                                " li %s, 0\n"
                                " j %s\n"
                                "%s:\n"
                                " li %s, 1\n"
                                "%s:\n",
                                fregName(L.reg), fregName(R.reg),
                                Ltrue,
                                tregName(d),
                                Lend,
                                Ltrue,
                                tregName(d),
                                Lend);
                            break;

                        case 'G': /* >= */
                            /* L >= R  ≡ !(L < R) */
                            fprintf(output,
                                " c.lt.s %s, %s\n"
                                " bc1t %s\n"
                                " li %s, 1\n"
                                " j %s\n"
                                "%s:\n"
                                " li %s, 0\n"
                                "%s:\n",
                                fregName(L.reg), fregName(R.reg),
                                Lfalse,
                                tregName(d),
                                Lend,
                                Lfalse,
                                tregName(d),
                                Lend);
                            break;

                        case 'L': /* <= */
                            fprintf(output,
                                " c.le.s %s, %s\n"
                                " bc1t %s\n"
                                " li %s, 0\n"
                                " j %s\n"
                                "%s:\n"
                                " li %s, 1\n"
                                "%s:\n",
                                fregName(L.reg), fregName(R.reg),
                                Ltrue,
                                tregName(d),
                                Lend,
                                Ltrue,
                                tregName(d),
                                Lend);
                            break;

                        case 'E': /* == */
                            fprintf(output,
                                " c.eq.s %s, %s\n"
                                " bc1t %s\n"
                                " li %s, 0\n"
                                " j %s\n"
                                "%s:\n"
                                " li %s, 1\n"
                                "%s:\n",
                                fregName(L.reg), fregName(R.reg),
                                Ltrue,
                                tregName(d),
                                Lend,
                                Ltrue,
                                tregName(d),
                                Lend);
                            break;

                        case 'N': /* != */
                            fprintf(output,
                                " c.eq.s %s, %s\n"
                                " bc1f %s\n"
                                " li %s, 0\n"
                                " j %s\n"
                                "%s:\n"
                                " li %s, 1\n"
                                "%s:\n",
                                fregName(L.reg), fregName(R.reg),
                                Ltrue,
                                tregName(d),
                                Lend,
                                Ltrue,
                                tregName(d),
                                Lend);
                            break;

                        default:
                            fprintf(stderr, "Unsupported float comparison '%c'\n", op);
                            exit(1);
                    }

                    Value out = { VAL_INT, d };
                    return out;
                }
                else {
                    /* int/bool/char comparisons & logical ops */
                    if (L.kind == VAL_FLOAT) L = floatToInt(L);
                    if (R.kind == VAL_FLOAT) R = floatToInt(R);

                    int d = getNextIntTemp();

                    switch (op) {
                        case '>':
                            fprintf(output, " sgt %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            break;

                        case '<':
                            fprintf(output, " slt %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            break;

                        case 'G': /* >=  => !(L < R) */
                            fprintf(output, " slt %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            fprintf(output, " seq %s, %s, $zero\n",
                                    tregName(d), tregName(d));
                            break;

                        case 'L': /* <=  => !(L > R) */
                            fprintf(output, " sgt %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            fprintf(output, " seq %s, %s, $zero\n",
                                    tregName(d), tregName(d));
                            break;

                        case 'E':
                            fprintf(output, " seq %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            break;

                        case 'N':
                            fprintf(output, " sne %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            break;

                        case '&':
                            /* logical AND: (L != 0) && (R != 0) */
                            fprintf(output, " sne %s, %s, $zero\n",
                                    tregName(L.reg), tregName(L.reg));
                            fprintf(output, " sne %s, %s, $zero\n",
                                    tregName(R.reg), tregName(R.reg));
                            fprintf(output, " and %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            break;

                        case '|':
                            /* logical OR: (L != 0) || (R != 0) */
                            fprintf(output, " or %s, %s, %s\n",
                                    tregName(d), tregName(L.reg), tregName(R.reg));
                            fprintf(output, " sne %s, %s, $zero\n",
                                    tregName(d), tregName(d));
                            break;

                        default:
                            fprintf(stderr, "Unsupported bool/int binop '%c'\n", op);
                            exit(1);
                    }

                    Value out = { VAL_INT, d };
                    return out;
                }
            }

            /* Fallback (should not really hit) */
            {
                int d = getNextIntTemp();
                fprintf(output, " li %s, 0\n", tregName(d));
                Value out = { VAL_INT, d };
                return out;
            }
        }

        /* if an expression node type not handled above */
        default: {
            int r = getNextIntTemp();
            fprintf(output, " li %s, 0\n", tregName(r));
            Value v = { VAL_INT, r };
            return v;
        }
    }
}

/* ============================================================
 * STATEMENTS
 * ============================================================ */

static void genStmt(ASTNode* node);

static void genAssignStoreFloat(int off, int fReg) {
    fprintf(output, " s.s %s, %d($sp)\n", fregName(fReg), off);
}

static void genAssignStoreInt(int off, int tReg) {
    fprintf(output, " sw %s, %d($sp)\n", tregName(tReg), off);
}

static void genStmt(ASTNode* node) {
    if (!node) return;

    switch (node->type) {

        case NODE_DECL: {
            int off = getVarOffset(node->data.name);
            fprintf(output, " # decl %s at %d\n", node->data.name, off);
            break;
        }

        case NODE_ASSIGN: {
            int off = getVarOffset(node->data.assign.var);
            if (off < 0) {
                fprintf(stderr, "assign to undeclared %s\n",
                        node->data.assign.var);
                exit(1);
            }

            /* determine variable type using a fake VAR node + inferExprType */
            ASTNode fakeVar;
            fakeVar.type = NODE_VAR;
            fakeVar.data.name = node->data.assign.var;
            const char* vtype = inferExprType(&fakeVar);

            Value val = genExpr(node->data.assign.value);

            if (isFloatTypeStr(vtype)) {
                if (val.kind == VAL_INT)
                    val = promoteToFloat(val);
                genAssignStoreFloat(off, val.reg);
            } else {
                if (val.kind == VAL_FLOAT)
                    val = floatToInt(val);
                genAssignStoreInt(off, val.reg);
            }
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

            int r1 = getNextIntTemp();
            int r2 = getNextIntTemp();

            fprintf(output, " # swap %s <-> %s\n", a, b);
            fprintf(output, " lw %s, %d($sp)\n", tregName(r1), offA);
            fprintf(output, " lw %s, %d($sp)\n", tregName(r2), offB);
            fprintf(output, " sw %s, %d($sp)\n", tregName(r2), offA);
            fprintf(output, " sw %s, %d($sp)\n", tregName(r1), offB);
            break;
        }

        case NODE_PRINT: {
            if (node->data.expr) {
                const char* t = inferExprType(node->data.expr);
                Value v = genExpr(node->data.expr);

                if (isFloatTypeStr(t)) {
                    if (v.kind == VAL_INT) v = promoteToFloat(v);
                    fprintf(output, " mov.s $f12, %s\n", fregName(v.reg));
                    fprintf(output, " li $v0, 2\n");
                }
                else if (t && strcmp(t, "char") == 0) {
                    if (v.kind == VAL_FLOAT) v = floatToInt(v);
                    fprintf(output, " li $v0, 11\n");
                    fprintf(output, " move $a0, %s\n", tregName(v.reg));
                }
                else {
                    if (v.kind == VAL_FLOAT) v = floatToInt(v);
                    fprintf(output, " li $v0, 1\n");
                    fprintf(output, " move $a0, %s\n", tregName(v.reg));
                }

                fprintf(output, " syscall\n");
            }

            /* newline */
            fprintf(output,
                " li $v0, 11\n"
                " li $a0, 10\n"
                " syscall\n");
            break;
        }

        case NODE_WRITE: {
            if (node->data.expr) {
                const char* t = inferExprType(node->data.expr);
                Value v = genExpr(node->data.expr);

                if (t && strcmp(t, "char") == 0) {
                    if (v.kind == VAL_FLOAT) v = floatToInt(v);
                    fprintf(output, " li $v0, 11\n");
                    fprintf(output, " move $a0, %s\n", tregName(v.reg));
                }
                else if (isFloatTypeStr(t)) {
                    if (v.kind == VAL_INT) v = promoteToFloat(v);
                    fprintf(output, " li $v0, 2\n");
                    fprintf(output, " mov.s $f12, %s\n", fregName(v.reg));
                }
                else {
                    if (v.kind == VAL_FLOAT) v = floatToInt(v);
                    fprintf(output, " li $v0, 1\n");
                    fprintf(output, " move $a0, %s\n", tregName(v.reg));
                }

                fprintf(output, " syscall\n");
            }
            break;
        }

        case NODE_WRITELN: {
            fprintf(output, " li $v0, 11\n");
            fprintf(output, " li $a0, 10\n");
            fprintf(output, " syscall\n");
            break;
        }

        case NODE_IF: {
            static int label = 0;
            char Lfalse[32], Lend[32];

            sprintf(Lfalse, "L_if_false_%d", label);
            sprintf(Lend,   "L_if_end_%d",  label++);

            Value cond = genExpr(node->data.ifstmt.condition);
            if (cond.kind == VAL_FLOAT)
                cond = floatToInt(cond);

            fprintf(output, " beqz %s, %s\n", tregName(cond.reg), Lfalse);

            genStmt(node->data.ifstmt.thenBranch);
            fprintf(output, " j %s\n%s:\n", Lend, Lfalse);

            if (node->data.ifstmt.elseBranch)
                genStmt(node->data.ifstmt.elseBranch);

            fprintf(output, "%s:\n", Lend);
            break;
        }

        case NODE_WHILE: {
            static int wlabel = 0;
            char Lstart[32], Lend[32];

            sprintf(Lstart, "L_while_start_%d", wlabel);
            sprintf(Lend,   "L_while_end_%d",   wlabel++);

            fprintf(output, "%s:\n", Lstart);

            Value cond = genExpr(node->data.whilestmt.condition);
            if (cond.kind == VAL_FLOAT)
                cond = floatToInt(cond);

            fprintf(output, " beqz %s, %s\n", tregName(cond.reg), Lend);

            genStmt(node->data.whilestmt.body);

            fprintf(output, " j %s\n%s:\n", Lstart, Lend);
            break;
        }

        case NODE_RACE: {
            static int raceLabel = 0;

            char Lleft[32], Lright[32], Lend[32];
            sprintf(Lleft,  "L_race_left_%d",  raceLabel);
            sprintf(Lright, "L_race_right_%d", raceLabel);
            sprintf(Lend,   "L_race_end_%d",   raceLabel++);

            fprintf(output,
                "\n # --- Begin race block ---\n"
                " # Strategy: first_wins\n"
                " li $t7, 0  # race_flag = 0\n"
                " j %s\n",
                Lleft
            );

            /* Left */
            fprintf(output, "%s:\n", Lleft);
            genStmt(node->data.racestmt.left);
            fprintf(output, " beqz $t7, %s\n", Lend);
            fprintf(output, " j %s\n", Lright);

            /* Right */
            fprintf(output, "%s:\n", Lright);
            genStmt(node->data.racestmt.right);
            fprintf(output, " beqz $t7, %s\n", Lend);
            fprintf(output, " j %s\n", Lend);

            /* End */
            fprintf(output,
                "%s:\n"
                " li $t7, 1 # first branch won\n"
                " # --- End race block ---\n\n",
                Lend
            );
            break;
        }

        case NODE_RETURN: {
            if (node->data.return_expr) {
                Value v = genExpr(node->data.return_expr);

                if (isFloatTypeStr(currentFunctionReturnType)) {
                    if (v.kind == VAL_INT) v = promoteToFloat(v);
                    /* float return in $f0 */
                    fprintf(output, " mov.s $f0, %s\n", fregName(v.reg));
                } else {
                    if (v.kind == VAL_FLOAT) v = floatToInt(v);
                    fprintf(output, " move $v0, %s\n", tregName(v.reg));
                }
            }
            fprintf(output, " j %s_epilogue\n", currentFunctionName);
            break;
        }

        case NODE_STMT_LIST:
            genStmt(node->data.stmtlist.stmt);
            genStmt(node->data.stmtlist.next);
            break;

        default:
            /* not handled as statement, ignore */
            break;
    }
}

/* ============================================================
 * FUNCTIONS
 * ============================================================ */

static void copyParamsIntoLocals(ASTNode* params) {
    int i = 0;
    ASTNode* p = params;

    while (p) {
        const char* name = NULL;
        const char* type = NULL;

        if (p->type == NODE_PARAM) {
            name = p->data.param.name;
            type = p->data.param.type;
            if (!name) break;

            int off = getVarOffset(name);

            /* For now: parameters always passed in $a0..$a3 as 32-bit.
             * For float params, caller should mfc1 to $aX beforehand. */
            if (i == 0) fprintf(output, " sw $a0, %d($sp)\n", off);
            else if (i == 1) fprintf(output, " sw $a1, %d($sp)\n", off);
            else if (i == 2) fprintf(output, " sw $a2, %d($sp)\n", off);
            else if (i == 3) fprintf(output, " sw $a3, %d($sp)\n", off);

            i++;
            break;
        }

        else if (p->type == NODE_PARAM_LIST) {
            ASTNode* item = p->data.list.item;
            if (item && item->type == NODE_PARAM) {
                name = item->data.param.name;
                type = item->data.param.type;
            }
            if (!name) {
                p = p->data.list.next;
                continue;
            }

            int off = getVarOffset(name);
            if (i == 0) fprintf(output, " sw $a0, %d($sp)\n", off);
            else if (i == 1) fprintf(output, " sw $a1, %d($sp)\n", off);
            else if (i == 2) fprintf(output, " sw $a2, %d($sp)\n", off);
            else if (i == 3) fprintf(output, " sw $a3, %d($sp)\n", off);

            i++;
            p = p->data.list.next;
        }

        else break;
    }
}

static void genFunction(ASTNode* func) {
    nextIntTemp = 0;
    nextFloatTemp = 0;

    const char* fname = func->data.func_decl.name;
    currentFunctionName = fname;
    currentFunctionReturnType = func->data.func_decl.returnType;

    const char* rtype = func->data.func_decl.returnType;
    addFunction((char*)fname, (char*)rtype, NULL, 0);

    fprintf(output, "\n.globl %s\n%s:\n", fname, fname);

    enterScope();

    if (func->data.func_decl.params)
        addParams(func->data.func_decl.params);

    predeclareBody(func->data.func_decl.body);

    int frame = localsBytes();

    fprintf(output,
        " addi $sp, $sp, -8\n"
        " sw $ra, 4($sp)\n"
        " sw $fp, 0($sp)\n"
        " move $fp, $sp\n"
    );

    if (frame > 0)
        fprintf(output, " addi $sp, $sp, -%d\n", frame);

    if (func->data.func_decl.params)
        copyParamsIntoLocals(func->data.func_decl.params);

    genStmt(func->data.func_decl.body);

    fprintf(output,
        "%s_epilogue:\n"
        " move $sp, $fp\n"
        " lw $fp, 0($sp)\n"
        " lw $ra, 4($sp)\n"
        " addi $sp, $sp, 8\n"
        " jr $ra\n",
        fname
    );

    exitScope();
}

static void genFuncList(ASTNode* list) {
    if (!list) return;

    if (list->type == NODE_FUNC_LIST) {
        genFuncList(list->data.list.item);
        genFuncList(list->data.list.next);
    }
    else if (list->type == NODE_FUNC_DECL) {
        genFunction(list);
    }
}

/* ============================================================
 * ENTRY
 * ============================================================ */

void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");
    if (!output) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(1);
    }

    initSymTab();

    fprintf(output,
        ".data\n\n"
        ".text\n"
        ".globl _start\n"
        "_start:\n"
        " jal main\n"
        " li $v0, 10\n"
        " syscall\n\n"
    );

    if (root->type == NODE_FUNC_LIST)
        genFuncList(root);
    else if (root->type == NODE_FUNC_DECL)
        genFunction(root);

    fclose(output);
}
