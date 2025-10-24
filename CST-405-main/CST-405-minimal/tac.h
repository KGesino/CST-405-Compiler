#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* ============================================================
 * TAC OPERATION ENUM
 * Includes float ops and 2D array support.
 * ============================================================ */
typedef enum {
    /* integer arithmetic */
    TAC_ADD, TAC_SUB, TAC_MUL, TAC_DIV,

    /* float arithmetic */
    TAC_FADD, TAC_FSUB, TAC_FMUL, TAC_FDIV,

    /* general statements */
    TAC_ASSIGN, TAC_PRINT, TAC_DECL,

    /* array operations */
    TAC_ARRAY_DECL, TAC_ARRAY_LOAD, TAC_ARRAY_STORE,
    TAC_ARRAY2D_DECL, TAC_ARRAY2D_LOAD, TAC_ARRAY2D_STORE,

    /* function/flow ops */
    TAC_LABEL, TAC_PARAM, TAC_CALL, TAC_RETURN,
    TAC_FUNC_BEGIN, TAC_FUNC_END
} TACOp;

/* ============================================================
 * TAC INSTRUCTION STRUCTURE
 * ============================================================ */
typedef struct TACInstr {
    TACOp op;
    char* arg1;
    char* arg2;
    char* result;
    int paramCount;
    struct TACInstr* next;
} TACInstr;

/* ============================================================
 * TAC LIST STRUCTURE
 * ============================================================ */
typedef struct {
    TACInstr* head;
    TACInstr* tail;
    int tempCount;
} TACList;

/* ============================================================
 * FUNCTION PROTOTYPES
 * ============================================================ */
void initTAC();
char* newTemp();
TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result);
void appendTAC(TACInstr* instr);
void generateTAC(ASTNode* node);
char* generateTACExpr(ASTNode* node);
void printTAC();

/* --- Optimization Passes --- */
void optimizeTAC();
void eliminateDeadCode();
void commonSubexprElimination();
void printOptimizedTAC();

#endif /* TAC_H */
