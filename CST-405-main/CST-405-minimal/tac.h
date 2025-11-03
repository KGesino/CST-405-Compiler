#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* ============================================================
 * TAC OPERATION ENUM
 * Includes arithmetic, float ops, array, function, boolean, and control flow.
 * ============================================================ */
typedef enum {
    /* integer arithmetic */
    TAC_ADD, TAC_SUB, TAC_MUL, TAC_DIV,

    /* float arithmetic */
    TAC_FADD, TAC_FSUB, TAC_FMUL, TAC_FDIV,

    /* relational operators */
    TAC_GT, TAC_LT, TAC_GE, TAC_LE, TAC_EQ, TAC_NE,

    /* boolean logic */
    TAC_AND, TAC_OR, TAC_NOT,

    /* general statements */
    TAC_ASSIGN, TAC_PRINT, TAC_DECL,

    /* array operations */
    TAC_ARRAY_DECL, TAC_ARRAY_LOAD, TAC_ARRAY_STORE,
    TAC_ARRAY2D_DECL, TAC_ARRAY2D_LOAD, TAC_ARRAY2D_STORE,

    /* function/flow ops */
    TAC_LABEL, TAC_PARAM, TAC_CALL, TAC_RETURN,
    TAC_FUNC_BEGIN, TAC_FUNC_END,

    /* control flow */
    TAC_IFZ,        /* Jump if condition is false (zero) */
    TAC_IFNZ,       /* Jump if condition is true  (nonzero) */
    TAC_GOTO        /* Unconditional jump */
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
    int labelCount;
} TACList;

/* ============================================================
 * FUNCTION PROTOTYPES
 * ============================================================ */

/* Initialization */
void initTAC(void);

/* Temp / label generators */
char* newTemp(void);
char* newLabel(void);

/* Instruction creation and management */
TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result);
void appendTAC(TACInstr* instr);

/* Code generation */
void generateTAC(ASTNode* node);
char* generateTACExpr(ASTNode* node);

/* Output */
void printTAC(void);

/* --- Optimization Passes --- */
void optimizeTAC(void);
void eliminateDeadCode(void);
void commonSubexprElimination(void);
void printOptimizedTAC(void);

#endif /* TAC_H */
