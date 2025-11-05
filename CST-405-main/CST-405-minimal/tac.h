#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* ============================================================
 * TAC OPERATION ENUM
 * ------------------------------------------------------------
 * Includes arithmetic, float ops, arrays, functions, boolean
 * logic, control flow operations, and parallel control.
 * ============================================================ */
typedef enum {
    /* ---------------- Integer Arithmetic ---------------- */
    TAC_ADD,        /* integer addition (+) */
    TAC_SUB,        /* integer subtraction (-) */
    TAC_MUL,        /* integer multiplication (*) */
    TAC_DIV,        /* integer division (/) */

    /* ---------------- Floating-Point Arithmetic ---------------- */
    TAC_FADD,       /* float addition (+) */
    TAC_FSUB,       /* float subtraction (-) */
    TAC_FMUL,       /* float multiplication (*) */
    TAC_FDIV,       /* float division (/) */

    /* ---------------- Relational Operators ---------------- */
    TAC_GT, TAC_LT, TAC_GE, TAC_LE,
    TAC_EQ, TAC_NE,

    /* ---------------- Boolean Logic ---------------- */
    TAC_AND, TAC_OR, TAC_NOT,

    /* ---------------- General Statements ---------------- */
    TAC_ASSIGN,     /* x = y */
    TAC_PRINT,      /* print x */
    TAC_DECL,       /* variable declaration */

    /* ---------------- Array Operations ---------------- */
    TAC_ARRAY_DECL, TAC_ARRAY_LOAD, TAC_ARRAY_STORE,
    TAC_ARRAY2D_DECL, TAC_ARRAY2D_LOAD, TAC_ARRAY2D_STORE,

    /* ---------------- Functions / Flow ---------------- */
    TAC_LABEL, TAC_PARAM, TAC_CALL, TAC_RETURN,
    TAC_FUNC_BEGIN, TAC_FUNC_END,

    /* ---------------- Control Flow ---------------- */
    TAC_IFZ,        /* jump if zero (false) */
    TAC_IFNZ,       /* jump if nonzero (true) */
    TAC_GOTO,       /* unconditional jump */

    /* ---------------- Parallel Control ----------------
     * TAC_RACE_START : Marks beginning of parallel race block.
     * TAC_RACE_END   : Marks end of race; 'first_wins' semantics apply.
     * -------------------------------------------------- */
    TAC_RACE_START, /* begin race { ... | ... } block */
    TAC_RACE_END    /* end race, first_wins logic applied */
} TACOp;

/* ============================================================
 * TAC INSTRUCTION STRUCTURE
 * ============================================================ */
typedef struct TACInstr {
    TACOp op;           /* operation code */
    char* arg1;         /* first operand */
    char* arg2;         /* second operand */
    char* result;       /* destination/result temp */
    int paramCount;     /* used for TAC_CALL */
    struct TACInstr* next;
} TACInstr;

/* ============================================================
 * TAC LIST STRUCTURE
 * ============================================================ */
typedef struct {
    TACInstr* head;
    TACInstr* tail;
    int tempCount;      /* for newTemp() naming */
    int labelCount;     /* for newLabel() naming */
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
