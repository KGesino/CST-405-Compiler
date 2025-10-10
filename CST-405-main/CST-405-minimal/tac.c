#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

TACList tacList;
TACList optimizedList;

void initTAC() {
    tacList.head = NULL;
    tacList.tail = NULL;
    tacList.tempCount = 0;
    optimizedList.head = NULL;
    optimizedList.tail = NULL;
}

/* ===== CHANGED: safer buffer & snprintf to avoid overflow on big temp counts ===== */
char* newTemp() {
    char* temp = malloc(32);
    if (!temp) { fprintf(stderr, "OOM in newTemp\n"); exit(1); }
    snprintf(temp, 32, "t%d", tacList.tempCount++);
    if (tacList.tempCount < 0) {  /* wrap paranoia */
        fprintf(stderr, "Error: TAC temp counter overflow\n");
        exit(1);
    }
    return temp;
}
/* ================================================================================= */

TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result) {
    TACInstr* instr = malloc(sizeof(TACInstr));
    instr->op = op;
    instr->arg1 = arg1 ? strdup(arg1) : NULL;
    instr->arg2 = arg2 ? strdup(arg2) : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->next = NULL;
    return instr;
}

void appendTAC(TACInstr* instr) {
    if (!tacList.head) {
        tacList.head = tacList.tail = instr;
    } else {
        tacList.tail->next = instr;
        tacList.tail = instr;
    }
}

void appendOptimizedTAC(TACInstr* instr) {
    if (!optimizedList.head) {
        optimizedList.head = optimizedList.tail = instr;
    } else {
        optimizedList.tail->next = instr;
        optimizedList.tail = instr;
    }
}

/* ========================================================================= */
/*                 EXPRESSION-LEVEL TAC GENERATION (UPDATED)                 */
/* ========================================================================= */
char* generateTACExpr(ASTNode* node) {
    if (!node) return NULL;
    
    switch(node->type) {
        case NODE_NUM: {
            char* temp = malloc(20);
            sprintf(temp, "%d", node->data.num);
            return temp;
        }
        
        case NODE_VAR:
            return strdup(node->data.name);
        
        case NODE_BINOP: {
            char* left = generateTACExpr(node->data.binop.left);
            char* right = generateTACExpr(node->data.binop.right);
            char* temp = newTemp();
            
            if (node->data.binop.op == '+') {
                appendTAC(createTAC(TAC_ADD, left, right, temp));
            } else if (node->data.binop.op == '-') {
                appendTAC(createTAC(TAC_SUB, left, right, temp));
            }
            return temp;
        }

        /* ===== ADDED FOR 1D ARRAYS ===== */
        case NODE_ARRAY_ACCESS: {
            char* idx = generateTACExpr(node->data.arraccess.index);
            char* tmp = newTemp();
            appendTAC(createTAC(TAC_ARRAY_LOAD, node->data.arraccess.name, idx, tmp));
            return tmp;
        }

        /* ===== NEW: 2D ARRAY ACCESS ===== */
        case NODE_ARRAY2D_ACCESS: {
            /* Compute row and column expressions */
            char* row = generateTACExpr(node->data.arr2d_access.row);
            char* col = generateTACExpr(node->data.arr2d_access.col);

            /* Create a temp for index calculation */
            char* indexTemp = newTemp();

            /* Record pseudo-instruction to indicate row/col indexing */
            appendTAC(createTAC(TAC_ARRAY2D_LOAD, row, col, indexTemp));

            /* Load the element value into another temp */
            char* tmp = newTemp();
            appendTAC(createTAC(TAC_ARRAY_LOAD, node->data.arr2d_access.name, indexTemp, tmp));
            return tmp;
        }
        /* ================================= */

        default:
            return NULL;
    }
}

/* ========================================================================= */
/*                 STATEMENT-LEVEL TAC GENERATION (UPDATED)                  */
/* ========================================================================= */
void generateTAC(ASTNode* node) {
    if (!node) return;
    
    switch(node->type) {
        case NODE_DECL:
            appendTAC(createTAC(TAC_DECL, NULL, NULL, node->data.name));
            break;

        /* ===== 1D Array Declaration ===== */
        case NODE_ARRAY_DECL: {
            char sizeBuf[32];
            sprintf(sizeBuf, "%d", node->data.arrdecl.size);
            appendTAC(createTAC(TAC_ARRAY_DECL, sizeBuf, NULL, node->data.arrdecl.name));
            break;
        }

        /* ===== NEW: 2D Array Declaration ===== */
        case NODE_ARRAY2D_DECL: {
            char rowsBuf[32], colsBuf[32];
            sprintf(rowsBuf, "%d", node->data.arr2d_decl.rows);
            sprintf(colsBuf, "%d", node->data.arr2d_decl.cols);
            appendTAC(createTAC(TAC_ARRAY2D_DECL, rowsBuf, colsBuf, node->data.arr2d_decl.name));
            break;
        }
        /* ===================================== */
            
        case NODE_ASSIGN: {
            char* expr = generateTACExpr(node->data.assign.value);
            appendTAC(createTAC(TAC_ASSIGN, expr, NULL, node->data.assign.var));
            break;
        }

        /* ===== 1D Array Element Assignment ===== */
        case NODE_ARRAY_ASSIGN: {
            char* idx = generateTACExpr(node->data.arrassign.index);
            char* val = generateTACExpr(node->data.arrassign.value);
            appendTAC(createTAC(TAC_ARRAY_STORE, idx, val, node->data.arrassign.var));
            break;
        }

        /* ===== NEW: 2D Array Element Assignment ===== */
        case NODE_ARRAY2D_ASSIGN: {
            char* row = generateTACExpr(node->data.arr2d_assign.row);
            char* col = generateTACExpr(node->data.arr2d_assign.col);
            char* val = generateTACExpr(node->data.arr2d_assign.value);

            /* Combine row & col for addressing */
            char* tempIndex = newTemp();
            appendTAC(createTAC(TAC_ARRAY2D_STORE, row, col, tempIndex));
            appendTAC(createTAC(TAC_ARRAY_STORE, tempIndex, val, node->data.arr2d_assign.var));
            break;
        }
        /* ======================================= */
        
        case NODE_PRINT: {
            char* expr = generateTACExpr(node->data.expr);
            appendTAC(createTAC(TAC_PRINT, expr, NULL, NULL));
            break;
        }

        case NODE_FUNC_DECL:
            appendTAC(createTAC(TAC_FUNC_BEGIN, NULL, NULL,
                                node->data.func_decl.name));
            appendTAC(createTAC(TAC_LABEL, NULL, NULL,
                                node->data.func_decl.name));
            // Generate TAC for function body
            generateTAC(node->data.func_decl.body);
            appendTAC(createTAC(TAC_FUNC_END, NULL, NULL,
                                node->data.func_decl.name));
            break;

        case NODE_FUNC_CALL: {
            // Generate TAC for each argument
            ASTNode* arg = node->data.func_call.args;
            int paramCount = 0;
            while (arg) {
                char* argVal = generateTACExpr(arg->data.list.item);
                appendTAC(createTAC(TAC_PARAM, argVal, NULL, NULL));
                paramCount++;
                arg = arg->data.list.next;
            }
            // Generate the call
            char* temp = newTemp();
            TACInstr* call = createTAC(TAC_CALL, node->data.func_call.name,
                                    NULL, temp);
            call->paramCount = paramCount;
            appendTAC(call);
            return temp;
        }

        case NODE_RETURN: {
            if (node->data.return_expr) {
                char* retVal = generateTACExpr(node->data.return_expr);
                appendTAC(createTAC(TAC_RETURN, retVal, NULL, NULL));
            } else {
                appendTAC(createTAC(TAC_RETURN, NULL, NULL, NULL));
            }
            break;
        }

        
        case NODE_STMT_LIST:
            generateTAC(node->data.stmtlist.stmt);
            generateTAC(node->data.stmtlist.next);
            break;
            
        default:
            break;
    }
}

/* ========================================================================= */
/*                        TAC PRINTING (UPDATED)                             */
/* ========================================================================= */
void printTAC() {
    printf("Unoptimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = tacList.head;
    int lineNum = 1;
    while (curr) {
        printf("%2d: ", lineNum++);
        switch(curr->op) {
            case TAC_DECL:
                printf("DECL %s\n", curr->result);
                break;
            case TAC_ADD:
                printf("%s = %s + %s\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_SUB:
                printf("%s = %s - %s\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_ASSIGN:
                printf("%s = %s\n", curr->result, curr->arg1);
                break;
            case TAC_PRINT:
                printf("PRINT %s\n", curr->arg1);
                break;

            /* ===== 1D ARRAYS ===== */
            case TAC_ARRAY_DECL:
                printf("ARRAY_DECL %s, size=%s\n", curr->result, curr->arg1);
                break;
            case TAC_ARRAY_LOAD:
                printf("%s = %s[%s]\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_ARRAY_STORE:
                printf("%s[%s] = %s\n", curr->result, curr->arg1, curr->arg2);
                break;

            /* ===== NEW: 2D ARRAYS ===== */
            case TAC_ARRAY2D_DECL:
                printf("ARRAY2D_DECL %s[%s][%s]\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_ARRAY2D_LOAD:
                printf("%s = index2D(%s, %s)\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_ARRAY2D_STORE:
                printf("index2D(%s, %s) -> %s\n", curr->arg1, curr->arg2, curr->result);
                break;
            case TAC_FUNC_BEGIN:
                printf("FUNC_BEGIN %s\n", curr->result);
                break;
            case TAC_LABEL:
                printf("LABEL %s\n", curr->result);
                break;
            case TAC_PARAM:
                printf("PARAM %s\n", curr->arg1);
                break;
            case TAC_CALL:
                printf("%s = CALL %s, %d\n", curr->result, curr->arg1, curr->paramCount);
                break;
            case TAC_RETURN:
                if (curr->arg1)
                    printf("RETURN %s\n", curr->arg1);
                else
                    printf("RETURN\n");
                break;
            case TAC_FUNC_END:
                printf("FUNC_END %s\n", curr->result);
                break;

        }
        curr = curr->next;
    }
}

/* Helper: simple numeric constant test (handles optional leading '-') */
static int isConstLike(const char* s) {
    if (!s || !*s) return 0;
    if (*s == '-') s++;
    for (; *s; ++s) if (!isdigit((unsigned char)*s)) return 0;
    return 1;
}

/* ===== CHANGED: dynamic copy-prop table to avoid stack overflow ===== */
typedef struct {
    char* var;
    char* value;
} VarValue;
/* =================================================================== */
// Simple optimization: constant folding and copy propagation
void optimizeTAC() {
    TACInstr* curr = tacList.head;

    /* dynamic propagation table */
    VarValue* values = NULL;
    int valueCount = 0;
    int valueCap = 0;
    #define VV_GROW(start) do { \
        int newCap = (valueCap == 0 ? (start) : valueCap * 2); \
        VarValue* nv = (VarValue*)realloc(values, newCap * sizeof(VarValue)); \
        if (!nv) { fprintf(stderr, "OOM growing VarValue table\n"); exit(1);} \
        values = nv; valueCap = newCap; \
    } while(0)

    while (curr) {
        TACInstr* newInstr = NULL;
        
        switch(curr->op) {
            case TAC_DECL:
                newInstr = createTAC(TAC_DECL, NULL, NULL, curr->result);
                break;

            /* arrays: pass-through with light propagation on indices/values */
            case TAC_ARRAY_DECL:
                newInstr = createTAC(TAC_ARRAY_DECL, curr->arg1, NULL, curr->result);
                break;

            case TAC_ARRAY_LOAD: {
                const char* idx = curr->arg2;
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, idx) == 0) { idx = values[i].value; break; }
                }
                newInstr = createTAC(TAC_ARRAY_LOAD, curr->arg1, (char*)idx, curr->result);
                break;
            }

            case TAC_ARRAY_STORE: {
                const char* idx = curr->arg1;
                const char* val = curr->arg2;
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, idx) == 0) { idx = values[i].value; break; }
                }
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, val) == 0) { val = values[i].value; break; }
                }
                newInstr = createTAC(TAC_ARRAY_STORE, (char*)idx, (char*)val, curr->result);
                break;
            }
                
            case TAC_ADD: {
                char* left = curr->arg1;
                char* right = curr->arg2;
                
                /* copy-prop lookups */
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, left) == 0) { left = values[i].value; break; }
                }
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, right) == 0) { right = values[i].value; break; }
                }
                
                /* constant folding */
                if (isConstLike(left) && isConstLike(right)) {
                    int result = atoi(left) + atoi(right);
                    char buf[32]; snprintf(buf, sizeof(buf), "%d", result);

                    if (valueCount >= valueCap) VV_GROW(256);
                    values[valueCount].var = strdup(curr->result);
                    values[valueCount].value = strdup(buf);
                    valueCount++;
                    
                    newInstr = createTAC(TAC_ASSIGN, buf, NULL, curr->result);
                } else {
                    newInstr = createTAC(TAC_ADD, left, right, curr->result);
                }
                break;
            }

            case TAC_SUB: {
                char* left = curr->arg1;
                char* right = curr->arg2;

                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, left) == 0) { left = values[i].value; break; }
                }
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, right) == 0) { right = values[i].value; break; }
                }

                if (isConstLike(left) && isConstLike(right)) {
                    int result = atoi(left) - atoi(right);
                    char buf[32]; snprintf(buf, sizeof(buf), "%d", result);

                    if (valueCount >= valueCap) VV_GROW(256);
                    values[valueCount].var = strdup(curr->result);
                    values[valueCount].value = strdup(buf);
                    valueCount++;

                    newInstr = createTAC(TAC_ASSIGN, buf, NULL, curr->result);
                } else {
                    newInstr = createTAC(TAC_SUB, left, right, curr->result);
                }
                break;
            }

            case TAC_ASSIGN: {
                char* value = curr->arg1;
                
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, value) == 0) { value = values[i].value; break; }
                }
                
                if (valueCount >= valueCap) VV_GROW(256);
                values[valueCount].var = strdup(curr->result);
                values[valueCount].value = strdup(value);
                valueCount++;
                
                newInstr = createTAC(TAC_ASSIGN, value, NULL, curr->result);
                break;
            }
            
            case TAC_PRINT: {
                char* value = curr->arg1;
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, value) == 0) { value = values[i].value; break; }
                }
                newInstr = createTAC(TAC_PRINT, value, NULL, NULL);
                break;
            }
        }
        
        if (newInstr) {
            appendOptimizedTAC(newInstr);
        }
        
        curr = curr->next;
    }

    /* optional: free propagation table (and its strings) */
    for (int i = 0; i < valueCount; ++i) {
        free(values[i].var);
        free(values[i].value);
    }
    free(values);
}

void printOptimizedTAC() {
    printf("Optimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = optimizedList.head;
    int lineNum = 1;
    while (curr) {
        printf("%2d: ", lineNum++);
        switch(curr->op) {
            case TAC_DECL:
                printf("DECL %s\n", curr->result);
                break;
            case TAC_ADD:
                printf("%s = %s + %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Runtime addition needed\n");
                break;
            case TAC_SUB:
                printf("%s = %s - %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Runtime subtraction needed\n");
                break;
            case TAC_ASSIGN:
                printf("%s = %s", curr->result, curr->arg1);
                if (isConstLike(curr->arg1)) {
                    printf("           // Constant value: %s\n", curr->arg1);
                } else {
                    printf("           // Copy value\n");
                }
                break;
            case TAC_PRINT:
                printf("PRINT %s", curr->arg1);
                if (isConstLike(curr->arg1)) {
                    printf("          // Print constant: %s\n", curr->arg1);
                } else {
                    printf("          // Print variable\n");
                }
                break;

            /* arrays */
            case TAC_ARRAY_DECL:
                printf("ARRAY_DECL %s, size=%s\n", curr->result, curr->arg1);
                break;
            case TAC_ARRAY_LOAD:
                printf("%s = %s[%s]\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_ARRAY_STORE:
                printf("%s[%s] = %s\n", curr->result, curr->arg1, curr->arg2);
                break;

            default:
                break;
        }
        curr = curr->next;
    }
}
