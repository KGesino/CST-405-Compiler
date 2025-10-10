#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* THREE-ADDRESS CODE (TAC)
 * Intermediate representation between AST and machine code
 * Each instruction has at most 3 operands (result = arg1 op arg2)
 * Makes optimization and code generation easier
 */

/* ===== EXTENDED TAC INSTRUCTION TYPES (WITH FUNCTIONS) ===== */
typedef enum {
    TAC_ADD, TAC_SUB, TAC_ASSIGN, TAC_PRINT, TAC_DECL,
    /* 1D Arrays */
    TAC_ARRAY_DECL, TAC_ARRAY_LOAD, TAC_ARRAY_STORE,
    /* 2D Arrays */
    TAC_ARRAY2D_DECL, TAC_ARRAY2D_LOAD, TAC_ARRAY2D_STORE,
    /* ===== FUNCTION SUPPORT ===== */
    TAC_LABEL,       // Function entry point
    TAC_PARAM,       // Function parameter passing
    TAC_CALL,        // Function call
    TAC_RETURN,      // Return statement
    TAC_FUNC_BEGIN,  // Function start marker
    TAC_FUNC_END     // Function end marker
} TACOp;

/* ===== UPDATED TAC INSTRUCTION STRUCTURE ===== */
typedef struct TACInstr {
    TACOp op;               /* Operation type */
    char* arg1;             /* Operand 1 */
    char* arg2;             /* Operand 2 */
    char* result;           /* Destination/result */
    int paramCount;         /* Used for TAC_CALL */
    struct TACInstr* next;  /* Linked list pointer */
} TACInstr;


/* TAC LIST MANAGEMENT */
typedef struct {
    TACInstr* head;    /* First instruction */
    TACInstr* tail;    /* Last instruction (for efficient append) */
    int tempCount;     /* Counter for temporary variables (t0, t1, ...) */
} TACList;

/* TAC GENERATION FUNCTIONS */
void initTAC();                                                    /* Initialize TAC lists */
char* newTemp();                                                   /* Generate new temp variable */
TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result); /* Create TAC instruction */
void appendTAC(TACInstr* instr);                                  /* Add instruction to list */
void generateTAC(ASTNode* node);                                  /* Convert AST to TAC */
char* generateTACExpr(ASTNode* node);                             /* Generate TAC for expression */

/* TAC OPTIMIZATION AND OUTPUT */
void printTAC();                                                   /* Display unoptimized TAC */
void optimizeTAC();                                                /* Apply optimizations */
void printOptimizedTAC();                                          /* Display optimized TAC */

#endif