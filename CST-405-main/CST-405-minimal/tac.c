#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"



/* ===================== Globals ===================== */
TACList tacList;
TACList optimizedList;

/* ===================== Utilities ===================== */
static char* xstrdup(const char* s) {
    if (!s) return NULL;
    char* d = (char*)malloc(strlen(s) + 1);
    if (!d) { fprintf(stderr, "OOM in strdup\n"); exit(1); }
    strcpy(d, s);
    return d;
}

static void appendToList(TACList* list, TACInstr* i) {
    if (!list->head) list->head = list->tail = i;
    else { list->tail->next = i; list->tail = i; }
}

/* ================= Initialization ================= */
void initTAC() {
    tacList.labelCount = 0;  // reset label counter
    tacList.head = tacList.tail = NULL;
    tacList.tempCount = 0;
    optimizedList.head = optimizedList.tail = NULL;
}

/* Generate new temporary variable safely */
char* newTemp() {
    char* temp = (char*)malloc(32);
    if (!temp) { fprintf(stderr, "OOM in newTemp\n"); exit(1); }
    snprintf(temp, 32, "t%d", tacList.tempCount++);
    return temp;
}
/* === NEW: Label counter and generator === */
char* newLabel() {
    char* label = (char*)malloc(32);
    if (!label) { fprintf(stderr, "OOM in newLabel\n"); exit(1); }
    snprintf(label, 32, "L%d", ++tacList.labelCount);
    return label;
}


/* Create new TAC instruction */
TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result) {
    TACInstr* instr = (TACInstr*)malloc(sizeof(TACInstr));
    if (!instr) { fprintf(stderr, "OOM in createTAC\n"); exit(1); }
    instr->op = op;
    instr->arg1 = arg1 ? xstrdup(arg1) : NULL;
    instr->arg2 = arg2 ? xstrdup(arg2) : NULL;
    instr->result = result ? xstrdup(result) : NULL;
    instr->paramCount = 0;
    instr->next = NULL;
    return instr;
}

/* Append TAC to main list */
void appendTAC(TACInstr* instr) {
    appendToList(&tacList, instr);
}

/* Append TAC to optimized list */
static void appendOptimizedTAC(TACInstr* instr) {
    appendToList(&optimizedList, instr);
}

/* ================= Expression-Level TAC ================= */
char* generateTACExpr(ASTNode* node) {
    if (!node) return NULL;

    switch (node->type) {
        case NODE_NUM: {
            char* temp = (char*)malloc(20);
            sprintf(temp, "%d", node->data.num);
            return temp;
        }

        case NODE_FLOAT: {
            char* temp = (char*)malloc(32);
            sprintf(temp, "%.6f", node->data.fnum);
            return temp;
        }

        case NODE_BOOL: {
            char* temp = (char*)malloc(8);
            sprintf(temp, "%d", node->data.num ? 1 : 0);
            return temp;
        }

        case NODE_VAR:
            return xstrdup(node->data.name);

        case NODE_UNOP: {
            char* expr = generateTACExpr(node->data.unop.expr);
            char* temp = newTemp();

            if (node->data.unop.op == '!') {
                appendTAC(createTAC(TAC_NOT, expr, NULL, temp));
            }
            return temp;
        }

        case NODE_BINOP: {
            char* left  = generateTACExpr(node->data.binop.left);
            char* right = generateTACExpr(node->data.binop.right);
            char* temp  = newTemp();

            int isFloat = (node->data.binop.left->type == NODE_FLOAT ||
                           node->data.binop.right->type == NODE_FLOAT);

            if (!isFloat) {
                switch (node->data.binop.op) {
                    case '+': appendTAC(createTAC(TAC_ADD, left, right, temp)); break;
                    case '-': appendTAC(createTAC(TAC_SUB, left, right, temp)); break;
                    case '*': appendTAC(createTAC(TAC_MUL, left, right, temp)); break;
                    case '/': appendTAC(createTAC(TAC_DIV, left, right, temp)); break;

                    /* relational */
                    case '>': appendTAC(createTAC(TAC_GT, left, right, temp)); break;
                    case '<': appendTAC(createTAC(TAC_LT, left, right, temp)); break;
                    case 'G': appendTAC(createTAC(TAC_GE, left, right, temp)); break;
                    case 'L': appendTAC(createTAC(TAC_LE, left, right, temp)); break;
                    case 'E': appendTAC(createTAC(TAC_EQ, left, right, temp)); break;
                    case 'N': appendTAC(createTAC(TAC_NE, left, right, temp)); break;

                    /* boolean logic */
                    case '&': appendTAC(createTAC(TAC_AND, left, right, temp)); break;
                    case '|': appendTAC(createTAC(TAC_OR, left, right, temp)); break;

                    default: break;
                }
            }
            else {
                if (node->data.binop.op == '+')
                    appendTAC(createTAC(TAC_FADD, left, right, temp));
                else if (node->data.binop.op == '-')
                    appendTAC(createTAC(TAC_FSUB, left, right, temp));
                else if (node->data.binop.op == '*')
                    appendTAC(createTAC(TAC_FMUL, left, right, temp));
                else if (node->data.binop.op == '/')
                    appendTAC(createTAC(TAC_FDIV, left, right, temp));
            }

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
        
                /* === NEW: IF STATEMENT HANDLING === */
        case NODE_IF: {
            // expected fields: condition, thenBranch, elseBranch
            char* condTemp = generateTACExpr(node->data.ifstmt.condition);
            char* falseLabel = newLabel();
            char* endLabel = newLabel();

            // Jump to else if condition is false
            appendTAC(createTAC(TAC_IFZ, condTemp, NULL, falseLabel));

            // THEN branch
            generateTAC(node->data.ifstmt.thenBranch);

            // Jump to end after THEN
            appendTAC(createTAC(TAC_GOTO, NULL, NULL, endLabel));

            // ELSE label
            appendTAC(createTAC(TAC_LABEL, NULL, NULL, falseLabel));

            // ELSE branch (if present)
            if (node->data.ifstmt.elseBranch)
                generateTAC(node->data.ifstmt.elseBranch);

            // END label
            appendTAC(createTAC(TAC_LABEL, NULL, NULL, endLabel));
            break;
        }

                case NODE_WHILE: {
            char* startLabel = newLabel();
            char* endLabel   = newLabel();

            appendTAC(createTAC(TAC_LABEL, NULL, NULL, startLabel));

            char* condTemp = generateTACExpr(node->data.whilestmt.condition);
            appendTAC(createTAC(TAC_IFZ, condTemp, NULL, endLabel));

            generateTAC(node->data.whilestmt.body);

            appendTAC(createTAC(TAC_GOTO, NULL, NULL, startLabel));
            appendTAC(createTAC(TAC_LABEL, NULL, NULL, endLabel));
            break;
        }

                /* === NEW: RACE (Parallel Choice) Handling === */
        case NODE_RACE: {
            // Expected fields: leftBranch, rightBranch, strategy ("first_wins")
            char* startLabel = newLabel();
            char* endLabel   = newLabel();

            appendTAC(createTAC(TAC_RACE_START, startLabel, NULL, "race_begin"));

            // Left branch
            generateTAC(node->data.racestmt.left);
            // Separator (optional visual marker or internal use)
            appendTAC(createTAC(TAC_LABEL, NULL, NULL, "RACE_BRANCH_SEPARATOR"));

            // Right branch
            generateTAC(node->data.racestmt.right);

            // End race with policy
            appendTAC(createTAC(TAC_RACE_END, endLabel, "first_wins", "race_end"));
            break;
        }



        default:
            break;
    }
}

/* ================= TAC Printing (unoptimized) ================= */
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
            case TAC_MUL:          printf("%s = %s * %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_DIV:          printf("%s = %s / %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_FADD:         printf("%s = %s +. %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_FSUB:         printf("%s = %s -. %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_FMUL:         printf("%s = %s *. %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_FDIV:         printf("%s = %s /. %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_GT:           printf("%s = (%s > %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_LT:           printf("%s = (%s < %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_GE:           printf("%s = (%s >= %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_LE:           printf("%s = (%s <= %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_EQ:           printf("%s = (%s == %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_NE:           printf("%s = (%s != %s)\n", curr->result, curr->arg1, curr->arg2); break;
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
            case TAC_IFZ:          printf("IFZ %s GOTO %s\n", curr->arg1, curr->result); break;
            case TAC_GOTO:         printf("GOTO %s\n", curr->result); break;
            case TAC_AND:          printf("%s = (%s && %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_OR:           printf("%s = (%s || %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_NOT:          printf("%s = !%s\n", curr->result, curr->arg1); break;
            case TAC_RACE_START:
                printf("RACE_START %s  (%s)\n", curr->arg1 ? curr->arg1 : "", curr->result ? curr->result : "");
                break;

            case TAC_RACE_END:
                printf("RACE_END %s  strategy=%s (%s)\n",
                       curr->arg1 ? curr->arg1 : "",
                       curr->arg2 ? curr->arg2 : "first_wins",
                       curr->result ? curr->result : "");
                break;


            default:               printf("(unknown TAC op)\n"); break;
        }
        curr = curr->next;
    }
}



/* ================= Optimization Helpers ================= */
static int isConstLike(const char* s) {
    if (!s || !*s) return 0;
    if (*s == '-') s++;
    for (; *s; ++s) if (!isdigit((unsigned char)*s)) return 0;
    return 1;
}

typedef struct { char* var; char* value; } VarValue;

/* map tempIndex -> (row,col) after ARRAY2D_LOAD/STORE */
typedef struct { char* temp; char* row; char* col; } Index2D;

/* lookup last propagated value for a symbol, else return input */
static const char* lookupProp(VarValue* vals, int count, const char* key) {
    if (!key) return NULL;
    for (int i = count - 1; i >= 0; --i) {
        if (vals[i].var && strcmp(vals[i].var, key) == 0) {
            return vals[i].value ? vals[i].value : key;
        }
    }
    return key;
}

/* build key strings for array constant memory */
static char* key1D(const char* arr, const char* idx) {
    char buf[256];
    snprintf(buf, sizeof(buf), "%s[%s]", arr, idx);
    return xstrdup(buf);
}
static char* key2D(const char* arr, const char* r, const char* c) {
    char buf[256];
    snprintf(buf, sizeof(buf), "%s[%s][%s]", arr, r, c);
    return xstrdup(buf);
}

/* ================= Phase 1: Constant folding/propagation =================
   - Folds +/-
   - Propagates scalars and temps
   - Tracks array writes of constants:
       arr[const] = const  => remembers key "arr[k]" -> value
       mat[idx2D_const] = const => remembers "mat[r][c]" -> value
   - On loads, if key known, replaces with ASSIGN constant
*/
void optimizeTAC() {
    /* reset optimized list */
    optimizedList.head = optimizedList.tail = NULL;

    TACInstr* curr = tacList.head;

    VarValue* values = NULL;   int vCount = 0, vCap = 0;
    Index2D*  idx2   = NULL;   int iCount = 0, iCap = 0;

    #define GROW_VALS(n) do { \
        if ((n) >= vCap) { int newCap = vCap? vCap*2 : 128; \
            values = (VarValue*)realloc(values, newCap*sizeof(VarValue)); \
            if(!values){fprintf(stderr,"OOM values\n"); exit(1);} \
            for(int _q=vCap; _q<newCap; ++_q){ values[_q].var=NULL; values[_q].value=NULL; } \
            vCap = newCap; \
        } \
    } while(0)

    #define GROW_IDX(n) do { \
        if ((n) >= iCap) { int newCap = iCap? iCap*2 : 64; \
            idx2 = (Index2D*)realloc(idx2, newCap*sizeof(Index2D)); \
            if(!idx2){fprintf(stderr,"OOM idx2\n"); exit(1);} \
            for(int _q=iCap; _q<newCap; ++_q){ idx2[_q].temp=NULL; idx2[_q].row=NULL; idx2[_q].col=NULL; } \
            iCap = newCap; \
        } \
    } while(0)

    while (curr) {
        TACInstr* out = NULL;

        switch (curr->op) {
            case TAC_DECL:
            case TAC_ARRAY_DECL:
            case TAC_ARRAY2D_DECL:
            case TAC_FUNC_BEGIN:
            case TAC_FUNC_END:
            case TAC_LABEL:
                out = createTAC(curr->op, curr->arg1, curr->arg2, curr->result);
                break;

            case TAC_PARAM: {
                const char* v = lookupProp(values, vCount, curr->arg1);
                out = createTAC(TAC_PARAM, (char*)(v?v:""), NULL, NULL);
                break;
            }

            case TAC_CALL: {
                out = createTAC(TAC_CALL, curr->arg1, curr->arg2, curr->result);
                out->paramCount = curr->paramCount;
                break;
            }

            case TAC_RETURN: {
                const char* v = lookupProp(values, vCount, curr->arg1);
                out = createTAC(TAC_RETURN, (char*)(v?v:NULL), NULL, NULL);
                break;
            }

            case TAC_ASSIGN: {
                const char* val = lookupProp(values, vCount, curr->arg1);
                /* record propagation for this target */
                GROW_VALS(vCount);
                values[vCount].var = xstrdup(curr->result);
                values[vCount].value = xstrdup(val?val:"");
                vCount++;
                out = createTAC(TAC_ASSIGN, (char*)(val?val:""), NULL, curr->result);
                break;
            }

            case TAC_ADD:
            case TAC_SUB: {
                const char* L = lookupProp(values, vCount, curr->arg1);
                const char* R = lookupProp(values, vCount, curr->arg2);
                if (isConstLike(L) && isConstLike(R)) {
                    int lv = atoi(L), rv = atoi(R);
                    int res = (curr->op==TAC_ADD)? (lv+rv) : (lv-rv);
                    char buf[32]; snprintf(buf, sizeof(buf), "%d", res);

                    GROW_VALS(vCount);
                    values[vCount].var = xstrdup(curr->result);
                    values[vCount].value = xstrdup(buf);
                    vCount++;

                    out = createTAC(TAC_ASSIGN, buf, NULL, curr->result);
                } else {
                    out = createTAC(curr->op, (char*)L, (char*)R, curr->result);
                }
                break;
            }

            case TAC_MUL:
            case TAC_DIV: {
                const char* L = lookupProp(values, vCount, curr->arg1);
                const char* R = lookupProp(values, vCount, curr->arg2);
                if (isConstLike(L) && isConstLike(R)) {
                    int lv = atoi(L), rv = atoi(R);
                    int res = (curr->op==TAC_MUL)? (lv*rv) : (rv ? lv/rv : 0);
                    char buf[32]; snprintf(buf, sizeof(buf), "%d", res);

                    GROW_VALS(vCount);
                    values[vCount].var = xstrdup(curr->result);
                    values[vCount].value = xstrdup(buf);
                    vCount++;

                    out = createTAC(TAC_ASSIGN, buf, NULL, curr->result);
                } else {
                    out = createTAC(curr->op, (char*)L, (char*)R, curr->result);
                }
                break;
            }


            case TAC_ARRAY2D_LOAD: {
                /* index2D(row,col)->resultTemp */
                const char* row = lookupProp(values, vCount, curr->arg1);
                const char* col = lookupProp(values, vCount, curr->arg2);
                /* record mapping from temp to (row,col) */
                GROW_IDX(iCount);
                idx2[iCount].temp = xstrdup(curr->result);
                idx2[iCount].row  = xstrdup(row?row:"");
                idx2[iCount].col  = xstrdup(col?col:"");
                iCount++;
                out = createTAC(TAC_ARRAY2D_LOAD, (char*)(row?row:""), (char*)(col?col:""), curr->result);
                break;
            }

            case TAC_ARRAY2D_STORE: {
                /* index2D(row,col)->temp (for store path) */
                const char* row = lookupProp(values, vCount, curr->arg1);
                const char* col = lookupProp(values, vCount, curr->arg2);
                /* record mapping */
                GROW_IDX(iCount);
                idx2[iCount].temp = xstrdup(curr->result); /* result is the tmp index on STORE */
                idx2[iCount].row  = xstrdup(row?row:"");
                idx2[iCount].col  = xstrdup(col?col:"");
                iCount++;
                out = createTAC(TAC_ARRAY2D_STORE, (char*)(row?row:""), (char*)(col?col:""), curr->result);
                break;
            }

            case TAC_ARRAY_STORE: {
                /* result = array name; arg1 = indexExpr or temp; arg2 = value */
                const char* idx = lookupProp(values, vCount, curr->arg1);
                const char* val = lookupProp(values, vCount, curr->arg2);

                /* If idx is a temp that came from index2D, record a 2D key */
                const char* rFound = NULL; const char* cFound = NULL;
                if (idx && idx[0]=='t') {
                    for (int k = iCount - 1; k >= 0; --k) {
                        if (idx2[k].temp && strcmp(idx2[k].temp, idx) == 0) {
                            rFound = idx2[k].row; cFound = idx2[k].col; break;
                        }
                    }
                }

                if (rFound && cFound && isConstLike(val)) {
                    /* remember mat[r][c] = const */
                    char* k = key2D(curr->result, rFound, cFound);
                    GROW_VALS(vCount);
                    values[vCount].var = k;
                    values[vCount].value = xstrdup(val);
                    vCount++;
                } else if (isConstLike(idx) && isConstLike(val)) {
                    char* k = key1D(curr->result, idx);
                    GROW_VALS(vCount);
                    values[vCount].var = k;
                    values[vCount].value = xstrdup(val);
                    vCount++;
                }

                out = createTAC(TAC_ARRAY_STORE, (char*)(idx?idx:""), (char*)(val?val:""), curr->result);
                break;
            }

            case TAC_ARRAY_LOAD: {
                /* arg1 = array, arg2 = index */
                const char* idx = lookupProp(values, vCount, curr->arg2);

                /* Try to fold load from recorded constant element */
                if (idx && idx[0]=='t') {
                    /* maybe it's an index2D temp */
                    const char* rFound = NULL; const char* cFound = NULL;
                    for (int k = iCount - 1; k >= 0; --k) {
                        if (idx2[k].temp && strcmp(idx2[k].temp, idx) == 0) {
                            rFound = idx2[k].row; cFound = idx2[k].col; break;
                        }
                    }
                    if (rFound && cFound) {
                        char* k = key2D(curr->arg1, rFound, cFound);
                        const char* v = lookupProp(values, vCount, k);
                        if (v && isConstLike(v)) {
                            /* replace with assign constant */
                            out = createTAC(TAC_ASSIGN, (char*)v, NULL, curr->result);
                            free(k);
                            break;
                        }
                        free(k);
                    }
                } else if (idx && isConstLike(idx)) {
                    char* k = key1D(curr->arg1, idx);
                    const char* v = lookupProp(values, vCount, k);
                    if (v && isConstLike(v)) {
                        out = createTAC(TAC_ASSIGN, (char*)v, NULL, curr->result);
                        free(k);
                        break;
                    }
                    free(k);
                }

                out = createTAC(TAC_ARRAY_LOAD, curr->arg1, (char*)(idx?idx:""), curr->result);
                break;
            }

            case TAC_PRINT: {
                const char* v = lookupProp(values, vCount, curr->arg1);
                out = createTAC(TAC_PRINT, (char*)(v?v:""), NULL, NULL);
                break;
            }
            default:
                out = createTAC(curr->op, curr->arg1, curr->arg2, curr->result);
                break;
        }

        appendOptimizedTAC(out);
        curr = curr->next;
    }

    /* cleanup tables */
    for (int i = 0; i < vCount; ++i) { free(values[i].var); free(values[i].value); }
    for (int i = 0; i < iCount; ++i) { free(idx2[i].temp); free(idx2[i].row); free(idx2[i].col); }
    free(values); free(idx2);
}

/* ================= Phase 2: Dead Code Elimination =================
   Simple DCE:
   - Collect all used names (from arg1/arg2) in optimizedList.
   - Drop instructions whose result is a temp (t*) and never used.
*/
void eliminateDeadCode() {
    /* Build used set */
    char** used = NULL; int uCount = 0, uCap = 0;
    #define USED_GROW do{ if(uCount>=uCap){uCap=uCap?uCap*2:256; used=(char**)realloc(used,uCap*sizeof(char*)); if(!used){fprintf(stderr,"OOM used\n");exit(1);} } }while(0)

    for (TACInstr* c = optimizedList.head; c; c = c->next) {
        if (c->arg1 && *c->arg1) { USED_GROW; used[uCount++] = xstrdup(c->arg1); }
        if (c->arg2 && *c->arg2) { USED_GROW; used[uCount++] = xstrdup(c->arg2); }
    }

    TACList newList = { NULL, NULL, 0 };
    for (TACInstr* c = optimizedList.head; c; c = c->next) {
        int keep = 1;

        /* Never drop side-effecting ops */
        if (c->op == TAC_PRINT || c->op == TAC_ARRAY_STORE ||
            c->op == TAC_PARAM || c->op == TAC_CALL ||
            c->op == TAC_RETURN || c->op == TAC_FUNC_BEGIN ||
            c->op == TAC_FUNC_END || c->op == TAC_LABEL) {
            keep = 1;
        } else if (c->result && c->result[0] == 't') {
            /* temp result: keep only if later used */
            keep = 0;
            for (int i = 0; i < uCount; ++i) {
                if (strcmp(used[i], c->result) == 0) { keep = 1; break; }
            }
        }

        if (keep) appendToList(&newList, createTAC(c->op, c->arg1, c->arg2, c->result));
    }

    /* Replace optimizedList with newList */
    optimizedList = newList;

    for (int i = 0; i < uCount; ++i) free(used[i]);
    free(used);
}

/* ================= Phase 3: Common Subexpression Elimination =================
   Very simple CSE: reuse earlier identical TAC_ADD/TAC_SUB (same op/operands).
   (No kill analysis; conservative improvement for toy compiler.)
*/
typedef struct { TACOp op; char* a; char* b; char* res; } ExprEntry;

void commonSubexprElimination() {
    ExprEntry* table = NULL; int tCount = 0, tCap = 0;
    #define TAB_GROW do{ if(tCount>=tCap){ tCap=tCap?tCap*2:128; table=(ExprEntry*)realloc(table,tCap*sizeof(ExprEntry)); if(!table){fprintf(stderr,"OOM cse\n");exit(1);} } }while(0)

    TACList newList = { NULL, NULL, 0 };

    for (TACInstr* c = optimizedList.head; c; c = c->next) {
        int reused = 0;

        if ((c->op == TAC_ADD || c->op == TAC_SUB) && c->arg1 && c->arg2) {
            for (int i = 0; i < tCount; ++i) {
                if (table[i].op == c->op &&
                    strcmp(table[i].a, c->arg1) == 0 &&
                    strcmp(table[i].b, c->arg2) == 0) {
                    /* found same expression: reuse */
                    appendToList(&newList, createTAC(TAC_ASSIGN, table[i].res, NULL, c->result));
                    reused = 1;
                    break;
                }
            }
            if (!reused) {
                TAB_GROW;
                table[tCount].op  = c->op;
                table[tCount].a   = xstrdup(c->arg1);
                table[tCount].b   = xstrdup(c->arg2);
                table[tCount].res = xstrdup(c->result);
                tCount++;
                appendToList(&newList, createTAC(c->op, c->arg1, c->arg2, c->result));
            }
        } else {
            appendToList(&newList, createTAC(c->op, c->arg1, c->arg2, c->result));
        }
    }

    /* swap in */
    optimizedList = newList;

    for (int i = 0; i < tCount; ++i) { free(table[i].a); free(table[i].b); free(table[i].res); }
    free(table);
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
            case TAC_MUL:          printf("%s = %s * %s\n", c->result, c->arg1, c->arg2); break;
            case TAC_DIV:          printf("%s = %s / %s\n", c->result, c->arg1, c->arg2); break;
            case TAC_FADD:         printf("%s = %s +. %s\n", c->result, c->arg1, c->arg2); break;
            case TAC_FSUB:         printf("%s = %s -. %s\n", c->result, c->arg1, c->arg2); break;
            case TAC_FMUL:         printf("%s = %s *. %s\n", c->result, c->arg1, c->arg2); break;
            case TAC_FDIV:         printf("%s = %s /. %s\n", c->result, c->arg1, c->arg2); break;

            case TAC_GT:           printf("%s = (%s > %s)\n", c->result, c->arg1, c->arg2); break;
            case TAC_LT:           printf("%s = (%s < %s)\n", c->result, c->arg1, c->arg2); break;
            case TAC_GE:           printf("%s = (%s >= %s)\n", c->result, c->arg1, c->arg2); break;
            case TAC_LE:           printf("%s = (%s <= %s)\n", c->result, c->arg1, c->arg2); break;
            case TAC_EQ:           printf("%s = (%s == %s)\n", c->result, c->arg1, c->arg2); break;
            case TAC_NE:           printf("%s = (%s != %s)\n", c->result, c->arg1, c->arg2); break;

            case TAC_AND:          printf("%s = (%s && %s)\n", c->result, c->arg1, c->arg2); break;
            case TAC_OR:           printf("%s = (%s || %s)\n", c->result, c->arg1, c->arg2); break;
            case TAC_NOT:          printf("%s = !%s\n", c->result, c->arg1); break;

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

            case TAC_IFZ:          printf("IFZ %s GOTO %s\n", c->arg1, c->result); break;
            case TAC_GOTO:         printf("GOTO %s\n", c->result); break;

            /* === NEW: Parallel Control === */
            case TAC_RACE_START:
                printf("RACE_START %s  (%s)\n",
                       c->arg1 ? c->arg1 : "",
                       c->result ? c->result : "");
                break;

            case TAC_RACE_END:
                printf("RACE_END %s  strategy=%s (%s)\n",
                       c->arg1 ? c->arg1 : "",
                       c->arg2 ? c->arg2 : "first_wins",
                       c->result ? c->result : "");
                break;

            default:
                printf("(unhandled TAC op)\n");
                break;
        }
        c = c->next;
    }
}

