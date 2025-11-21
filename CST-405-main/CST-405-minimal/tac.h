#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* ============================================================
 * THREE-ADDRESS CODE (TAC) OPERATION ENUM
 * ------------------------------------------------------------
 * Supports arithmetic, floating-point ops, arrays, functions,
 * boolean logic, control flow, and I/O (print/write/writeln).
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
    TAC_AND, TAC_OR, TAC_NOT, TAC_NEG,

    /* ---------------- Assignments ---------------- */
    TAC_ASSIGN,     /* x = y */

    /* ---------------- Swap ---------------- */
    TAC_SWAP,       /* swap x y */

    /* ---------------- Input/Output ---------------- */
    TAC_PRINT,      /* print (standard print) */
    TAC_WRITE,      /* write without newline */
    TAC_WRITELN,    /* write newline only */

    /* ---------------- Declarations ---------------- */
    TAC_DECL,       /* variable declaration */

    /* ---------------- Array Operations ---------------- */
    TAC_ARRAY_DECL,
    TAC_ARRAY_LOAD,
    TAC_ARRAY_STORE,
    TAC_ARRAY2D_DECL,
    TAC_ARRAY2D_LOAD,
    TAC_ARRAY2D_STORE,

    /* ---------------- Functions & Calls ---------------- */
    TAC_LABEL,
    TAC_PARAM,
    TAC_ARRAY_PARAM,
    TAC_CALL,
    TAC_RETURN,
    TAC_FUNC_BEGIN,
    TAC_FUNC_END,

    /* ---------------- Control Flow ----------------
     * Used for both IF and WHILE constructs.
     * ---------------------------------------------- */
    TAC_IFZ,        /* jump if zero (false) */
    TAC_IFNZ,       /* jump if nonzero (true) */
    TAC_GOTO,       /* unconditional jump */

    /* ---------------- Parallel Control ----------------
     * Used for: race { ... | ... } first_wins
     * ---------------------------------------------- */
    TAC_RACE_START, /* begin race block */
    TAC_RACE_END    /* end race (first_wins) */
} TACOp;

/* ============================================================
 * TAC INSTRUCTION STRUCTURE
 * ============================================================ */
typedef struct TACInstr {
    TACOp op;               /* operation code */
    char* arg1;             /* first operand */
    char* arg2;             /* second operand */
    char* result;           /* destination/result temp */
    int paramCount;         /* used for TAC_CALL */
    int isArrayParam;       /* 1 if arg1 is an array parameter */
    struct TACInstr* next;
} TACInstr;

/* ============================================================
 * TAC LIST STRUCTURE
 * ============================================================ */
typedef struct {
    TACInstr* head;
    TACInstr* tail;
    int tempCount;          /* temporary variable counter */
    int labelCount;         /* label counter for control flow */
} TACList;

/* ============================================================
 * FUNCTION PROTOTYPES
 * ============================================================ */

/* --- Initialization --- */
void initTAC(void);

/* --- Temporary and Label Generators --- */
char* newTemp(void);
char* newLabel(void);

/* --- Instruction Management --- */
TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result);
void appendTAC(TACInstr* instr);

/* --- Code Generation --- */
void generateTAC(ASTNode* node);
char* generateTACExpr(ASTNode* node);

/* --- Output --- */
void printTAC(void);

/* --- Optimization Passes --- */
void optimizeTAC(void);
void constantFoldingAndPropagation(void);
void eliminateDeadCode(void);
void commonSubexprElimination(void);
void printOptimizedTAC(void);

#endif /* TAC_H */
