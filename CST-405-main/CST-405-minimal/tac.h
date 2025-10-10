#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* THREE-ADDRESS CODE (TAC)
 * Intermediate representation between AST and machine code
 * Each instruction has at most 3 operands (result = arg1 op arg2)
 * Makes optimization and code generation easier
 */

/* TAC INSTRUCTION TYPES */
typedef enum {
    TAC_ADD,     /* Addition: result = arg1 + arg2 */
    TAC_SUB,    /* Subtraction: result = arg1 - arg2 */
    TAC_ASSIGN,  /* Assignment: result = arg1 */
    TAC_PRINT,   /* Print: print(arg1) */
    TAC_DECL,     /* Declaration: declare result */
    /* ===== Added for 1d arrays ===== */
    TAC_ARRAY_DECL,  /* Array declaration: result = name, arg1 = size */
    TAC_ARRAY_LOAD,  /* Load element: result = a[index]  (result=temp, arg1=array, arg2=index) */
    TAC_ARRAY_STORE,  /* Store element: a[index] = value  (result=array, arg1=index, arg2=value) */
    /* ============================ */
    /* ===== NEW: Added for 2D arrays ===== */
    TAC_ARRAY2D_DECL,   /* 2D array declaration: result = name, arg1 = rows, arg2 = cols */
    TAC_ARRAY2D_LOAD,   /* Load element: result = a[row][col] (result=temp, arg1=array, arg2=indexExpr) */
    TAC_ARRAY2D_STORE   /* Store element: a[row][col] = value (result=array, arg1=indexExpr, arg2=value) */
    /* =================================== */
} TACOp;

/* TAC INSTRUCTION STRUCTURE */
typedef struct TACInstr {
    TACOp op;               /* Operation type */
    char* arg1;             /* First operand (if needed) */
    char* arg2;             /* Second operand (for binary ops) */
    char* result;           /* Result/destination */
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