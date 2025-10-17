#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

TACList tacList;
TACList optimizedList;

/* ================= Initialization ================= */
void initTAC() {
    tacList.head = tacList.tail = NULL;
    tacList.tempCount = 0;
    optimizedList.head = optimizedList.tail = NULL;
}

/* Generate new temporary variable safely */
char* newTemp() {
    char* temp = (char*)malloc(32);
    if (!temp) { fprintf(stderr, "OOM in newTemp\n"); exit(1); }
    snprintf(temp, 32, "t%d", tacList.tempCount++);
    if (tacList.tempCount < 0) {
        fprintf(stderr, "Error: TAC temp counter overflow\n");
        exit(1);
    }
    return temp;
}

/* Create new TAC instruction */
TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result) {
    TACInstr* instr = (TACInstr*)malloc(sizeof(TACInstr));
    if (!instr) { fprintf(stderr, "OOM in createTAC\n"); exit(1); }
    instr->op = op;
    instr->arg1 = arg1 ? strdup(arg1) : NULL;
    instr->arg2 = arg2 ? strdup(arg2) : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->paramCount = 0;
    instr->next = NULL;
    return instr;
}

/* Append TAC to main list */
void appendTAC(TACInstr* instr) {
    if (!tacList.head)
        tacList.head = tacList.tail = instr;
    else {
        tacList.tail->next = instr;
        tacList.tail = instr;
    }
}

/* Append TAC to optimized list */
static void appendOptimizedTAC(TACInstr* instr) {
    if (!optimizedList.head)
        optimizedList.head = optimizedList.tail = instr;
    else {
        optimizedList.tail->next = instr;
        optimizedList.tail = instr;
    }
}

/* ================= Expression-Level TAC ================= */
char* generateTACExpr(ASTNode* node) {
    if (!node) return NULL;

    switch (node->type) {
        case NODE_NUM: {
            char* temp = (char*)malloc(20);
            if (!temp) { fprintf(stderr, "OOM in generateTACExpr\n"); exit(1); }
            sprintf(temp, "%d", node->data.num);
            return temp;
        }

        case NODE_VAR:
            return strdup(node->data.name);

        case NODE_BINOP: {
            char* left = generateTACExpr(node->data.binop.left);
            char* right = generateTACExpr(node->data.binop.right);
            char* temp = newTemp();

            if (node->data.binop.op == '+')
                appendTAC(createTAC(TAC_ADD, left, right, temp));
            else if (node->data.binop.op == '-')
                appendTAC(createTAC(TAC_SUB, left, right, temp));

            return temp;
        }

        case NODE_ARRAY_ACCESS: {
            char* idx = generateTACExpr(node->data.arraccess.index);
            char* tmp = newTemp();
            appendTAC(createTAC(TAC_ARRAY_LOAD, node->data.arraccess.name, idx, tmp));
            return tmp;
        }

        case NODE_ARRAY2D_ACCESS: {
            char* row = generateTACExpr(node->data.arr2d_access.row);
            char* col = generateTACExpr(node->data.arr2d_access.col);
            char* indexTemp = newTemp();
            appendTAC(createTAC(TAC_ARRAY2D_LOAD, row, col, indexTemp));
            char* tmp = newTemp();
            appendTAC(createTAC(TAC_ARRAY_LOAD, node->data.arr2d_access.name, indexTemp, tmp));
            return tmp;
        }

        default:
            return NULL;
    }
}

/* ================= Statement-Level TAC ================= */
void generateTAC(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_FUNC_LIST:
            generateTAC(node->data.list.item);
            generateTAC(node->data.list.next);
            break;

        case NODE_DECL:
            appendTAC(createTAC(TAC_DECL, NULL, NULL, node->data.name));
            break;

        case NODE_ARRAY_DECL: {
            char buf[32];
            sprintf(buf, "%d", node->data.arrdecl.size);
            appendTAC(createTAC(TAC_ARRAY_DECL, buf, NULL, node->data.arrdecl.name));
            break;
        }

        case NODE_ARRAY2D_DECL: {
            char rb[32], cb[32];
            sprintf(rb, "%d", node->data.arr2d_decl.rows);
            sprintf(cb, "%d", node->data.arr2d_decl.cols);
            appendTAC(createTAC(TAC_ARRAY2D_DECL, rb, cb, node->data.arr2d_decl.name));
            break;
        }

        case NODE_ASSIGN: {
            char* expr = generateTACExpr(node->data.assign.value);
            appendTAC(createTAC(TAC_ASSIGN, expr, NULL, node->data.assign.var));
            break;
        }

        case NODE_ARRAY_ASSIGN: {
            char* idx = generateTACExpr(node->data.arrassign.index);
            char* val = generateTACExpr(node->data.arrassign.value);
            appendTAC(createTAC(TAC_ARRAY_STORE, idx, val, node->data.arrassign.var));
            break;
        }

        case NODE_ARRAY2D_ASSIGN: {
            char* row = generateTACExpr(node->data.arr2d_assign.row);
            char* col = generateTACExpr(node->data.arr2d_assign.col);
            char* val = generateTACExpr(node->data.arr2d_assign.value);
            char* tmpIndex = newTemp();
            appendTAC(createTAC(TAC_ARRAY2D_STORE, row, col, tmpIndex));
            appendTAC(createTAC(TAC_ARRAY_STORE, tmpIndex, val, node->data.arr2d_assign.var));
            break;
        }

        case NODE_PRINT: {
            char* expr = generateTACExpr(node->data.expr);
            appendTAC(createTAC(TAC_PRINT, expr, NULL, NULL));
            break;
        }

        case NODE_FUNC_DECL:
            appendTAC(createTAC(TAC_FUNC_BEGIN, NULL, NULL, node->data.func_decl.name));
            appendTAC(createTAC(TAC_LABEL, NULL, NULL, node->data.func_decl.name));
            generateTAC(node->data.func_decl.body);
            appendTAC(createTAC(TAC_FUNC_END, NULL, NULL, node->data.func_decl.name));
            break;

        case NODE_FUNC_CALL: {
            ASTNode* arg = node->data.func_call.args;
            int count = 0;
            while (arg) {
                char* val = generateTACExpr(arg->data.list.item);
                appendTAC(createTAC(TAC_PARAM, val, NULL, NULL));
                count++;
                arg = arg->data.list.next;
            }
            char* temp = newTemp();
            TACInstr* call = createTAC(TAC_CALL, node->data.func_call.name, NULL, temp);
            call->paramCount = count;
            appendTAC(call);
            break;
        }

        case NODE_RETURN:
            if (node->data.return_expr) {
                char* retVal = generateTACExpr(node->data.return_expr);
                appendTAC(createTAC(TAC_RETURN, retVal, NULL, NULL));
            } else {
                appendTAC(createTAC(TAC_RETURN, NULL, NULL, NULL));
            }
            break;

        case NODE_STMT_LIST:
            generateTAC(node->data.stmtlist.stmt);
            generateTAC(node->data.stmtlist.next);
            break;

        default:
            break;
    }
}

/* ================= TAC Printing ================= */
void printTAC() {
    printf("Unoptimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = tacList.head;
    int lineNum = 1;
    while (curr) {
        printf("%2d: ", lineNum++);
        switch (curr->op) {
            case TAC_DECL:         printf("DECL %s\n", curr->result); break;
            case TAC_ADD:          printf("%s = %s + %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_SUB:          printf("%s = %s - %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_ASSIGN:       printf("%s = %s\n", curr->result, curr->arg1); break;
            case TAC_PRINT:        printf("PRINT %s\n", curr->arg1); break;

            case TAC_ARRAY_DECL:   printf("ARRAY_DECL %s, size=%s\n", curr->result, curr->arg1); break;
            case TAC_ARRAY_LOAD:   printf("%s = %s[%s]\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_ARRAY_STORE:  printf("%s[%s] = %s\n", curr->result, curr->arg1, curr->arg2); break;

            case TAC_ARRAY2D_DECL: printf("ARRAY2D_DECL %s[%s][%s]\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_ARRAY2D_LOAD: printf("%s = index2D(%s, %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_ARRAY2D_STORE:printf("index2D(%s,%s)->%s\n", curr->arg1, curr->arg2, curr->result); break;

            case TAC_FUNC_BEGIN:   printf("FUNC_BEGIN %s\n", curr->result); break;
            case TAC_FUNC_END:     printf("FUNC_END %s\n", curr->result); break;
            case TAC_LABEL:        printf("LABEL %s\n", curr->result); break;
            case TAC_PARAM:        printf("PARAM %s\n", curr->arg1); break;
            case TAC_CALL:         printf("%s = CALL %s (%d params)\n", curr->result, curr->arg1, curr->paramCount); break;
            case TAC_RETURN:       if (curr->arg1) printf("RETURN %s\n", curr->arg1); else printf("RETURN\n"); break;
        }
        curr = curr->next;
    }
}

/* ================= Optimization ================= */
static int isConstLike(const char* s) {
    if (!s || !*s) return 0;
    if (*s == '-') s++;
    for (; *s; ++s) if (!isdigit((unsigned char)*s)) return 0;
    return 1;
}

typedef struct {
    char* var;
    char* value;
} VarValue;

/* Helper: lookup with NULL guards */
static const char* lookupProp(VarValue* vals, int count, const char* key) {
    if (!key) return NULL;
    for (int i = count - 1; i >= 0; --i) {
        if (vals[i].var && strcmp(vals[i].var, key) == 0) {
            return vals[i].value ? vals[i].value : key;
        }
    }
    return key;
}

void optimizeTAC() {
    TACInstr* curr = tacList.head;
    VarValue* values = NULL;
    int count = 0, cap = 0;

    #define GROW(n) do { \
        int nc = (cap == 0 ? (n) : cap * 2); \
        VarValue* nv = (VarValue*)realloc(values, nc * sizeof(VarValue)); \
        if (!nv) { fprintf(stderr, "OOM growing VarValue table\n"); exit(1); } \
        /* Initialize new slots to NULL to avoid strcmp(NULL, ...) */ \
        for (int _k = cap; _k < nc; ++_k) { nv[_k].var = NULL; nv[_k].value = NULL; } \
        values = nv; \
        cap = nc; \
    } while (0)

    /* Optional: pre-allocate to reduce reallocs and ensure non-zero cap */
    if (cap == 0) GROW(128);

    while (curr) {
        TACInstr* n = NULL;

        switch (curr->op) {
            case TAC_DECL: {
                n = createTAC(TAC_DECL, NULL, NULL, curr->result);
                break;
            }

            case TAC_ARRAY_DECL: {
                n = createTAC(TAC_ARRAY_DECL, curr->arg1, NULL, curr->result);
                break;
            }

            case TAC_ARRAY_LOAD: {
                const char* array = curr->arg1;
                const char* idx   = lookupProp(values, count, curr->arg2);
                n = createTAC(TAC_ARRAY_LOAD, (char*)array, (char*)idx, curr->result);
                break;
            }

            case TAC_ARRAY_STORE: {
                const char* idx = lookupProp(values, count, curr->arg1);
                const char* val = lookupProp(values, count, curr->arg2);
                n = createTAC(TAC_ARRAY_STORE, (char*)idx, (char*)val, curr->result);
                break;
            }

            case TAC_ARRAY2D_DECL: {
                n = createTAC(TAC_ARRAY2D_DECL, curr->arg1, curr->arg2, curr->result);
                break;
            }

            case TAC_ARRAY2D_LOAD: {
                const char* row = lookupProp(values, count, curr->arg1);
                const char* col = lookupProp(values, count, curr->arg2);
                n = createTAC(TAC_ARRAY2D_LOAD, (char*)row, (char*)col, curr->result);
                break;
            }

            case TAC_ARRAY2D_STORE: {
                const char* row = lookupProp(values, count, curr->arg1);
                const char* col = lookupProp(values, count, curr->arg2);
                n = createTAC(TAC_ARRAY2D_STORE, (char*)row, (char*)col, curr->result);
                break;
            }

            case TAC_ADD:
            case TAC_SUB: {
                const char* l = lookupProp(values, count, curr->arg1);
                const char* r = lookupProp(values, count, curr->arg2);

                if (isConstLike(l) && isConstLike(r)) {
                    int lv = atoi(l);
                    int rv = atoi(r);
                    int res = (curr->op == TAC_ADD) ? (lv + rv) : (lv - rv);
                    char buf[32]; snprintf(buf, sizeof(buf), "%d", res);

                    if (count >= cap) GROW(128);
                    values[count].var = strdup(curr->result);
                    values[count].value = strdup(buf);
                    count++;

                    n = createTAC(TAC_ASSIGN, buf, NULL, curr->result);
                } else {
                    n = createTAC(curr->op, (char*)l, (char*)r, curr->result);
                }
                break;
            }

            case TAC_ASSIGN: {
                const char* v = lookupProp(values, count, curr->arg1);

                if (count >= cap) GROW(128);
                values[count].var = strdup(curr->result);
                values[count].value = strdup(v ? v : "");
                count++;

                n = createTAC(TAC_ASSIGN, (char*)(v ? v : ""), NULL, curr->result);
                break;
            }

            case TAC_PRINT: {
                const char* v = lookupProp(values, count, curr->arg1);
                n = createTAC(TAC_PRINT, (char*)(v ? v : ""), NULL, NULL);
                break;
            }

            /* ==== Function related: pass-through safely ==== */
            case TAC_FUNC_BEGIN:
            case TAC_FUNC_END:
            case TAC_LABEL: {
                n = createTAC(curr->op, curr->arg1, curr->arg2, curr->result);
                break;
            }

            case TAC_PARAM: {
                const char* v = lookupProp(values, count, curr->arg1);
                n = createTAC(TAC_PARAM, (char*)(v ? v : ""), NULL, NULL);
                break;
            }

            case TAC_CALL: {
                /* function calls can clobber registers; keep as-is, but keep paramCount */
                n = createTAC(TAC_CALL, curr->arg1, curr->arg2, curr->result);
                n->paramCount = curr->paramCount;
                /* we could also clear propagation here if we tracked liveness */
                break;
            }

            case TAC_RETURN: {
                const char* v = lookupProp(values, count, curr->arg1);
                n = createTAC(TAC_RETURN, (char*)(v ? v : NULL), NULL, NULL);
                break;
            }
        }

        appendOptimizedTAC(n);
        curr = curr->next;
    }

    for (int i = 0; i < count; ++i) {
        free(values[i].var);
        free(values[i].value);
    }
    free(values);
}

/* ================= Optimized TAC Printing ================= */
void printOptimizedTAC() {
    printf("Optimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* c = optimizedList.head; 
    int i = 1;
    while (c) {
        printf("%2d: ", i++);
        switch (c->op) {
            case TAC_DECL:         printf("DECL %s\n", c->result); break;
            case TAC_ASSIGN:       printf("%s = %s\n", c->result, c->arg1); break;
            case TAC_ADD:          printf("%s = %s + %s\n", c->result, c->arg1, c->arg2); break;
            case TAC_SUB:          printf("%s = %s - %s\n", c->result, c->arg1, c->arg2); break;
            case TAC_PRINT:        printf("PRINT %s\n", c->arg1); break;

            case TAC_ARRAY_DECL:   printf("ARRAY_DECL %s, size=%s\n", c->result, c->arg1); break;
            case TAC_ARRAY_LOAD:   printf("%s = %s[%s]\n", c->result, c->arg1, c->arg2); break;
            case TAC_ARRAY_STORE:  printf("%s[%s] = %s\n", c->result, c->arg1, c->arg2); break;

            case TAC_ARRAY2D_DECL: printf("ARRAY2D_DECL %s[%s][%s]\n", c->result, c->arg1, c->arg2); break;
            case TAC_ARRAY2D_LOAD: printf("%s = index2D(%s, %s)\n", c->result, c->arg1, c->arg2); break;
            case TAC_ARRAY2D_STORE:printf("index2D(%s,%s)->%s\n", c->arg1, c->arg2, c->result); break;

            case TAC_FUNC_BEGIN:   printf("FUNC_BEGIN %s\n", c->result); break;
            case TAC_FUNC_END:     printf("FUNC_END %s\n", c->result); break;
            case TAC_LABEL:        printf("LABEL %s\n", c->result); break;
            case TAC_PARAM:        printf("PARAM %s\n", c->arg1); break;
            case TAC_CALL:         printf("%s = CALL %s (%d params)\n", c->result, c->arg1, c->paramCount); break;
            case TAC_RETURN:       if (c->arg1) printf("RETURN %s\n", c->arg1); else printf("RETURN\n"); break;
        }
        c = c->next;
    }
}
