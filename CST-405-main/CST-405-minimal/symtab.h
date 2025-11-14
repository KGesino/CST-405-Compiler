#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>
#include <string.h>
#include "ast.h"

#define MAX_VARS 10000

/* ============================================================
 * SYMBOL ENTRY
 * Represents variables, arrays, and functions.
 * ============================================================ */
typedef struct {
    char* name;         /* Identifier */
    char* type;         /* "int", "float", "bool", "void" */
    int offset;         /* Stack offset */
    int size;           /* Size in bytes (4 for int/float/bool) */
    int isArray;        /* 0 = scalar, 1 = 1D array, 2 = 2D array */
    int dim1;           /* Rows / elements */
    int dim2;           /* Columns (for 2D arrays) */

    /* Function metadata */
    int isFunction;     /* 1 if function */
    int paramCount;     /* Number of parameters */
    char** paramTypes;  /* Parameter types */

    /* Float and Boolean tracking */
    int isFloat;        /* 1 if float or float array */
    int isBool;         /* 1 if bool or bool array */
} Symbol;

/* ============================================================
 * SCOPE STRUCTURE
 * Each scope maintains its own symbol entries.
 * ============================================================ */
typedef struct Scope {
    Symbol vars[MAX_VARS];
    int count;
    int nextOffset;         /* Stack frame offset tracker */
    struct Scope* parent;   /* Link to parent (outer) scope */
} Scope;

/* ============================================================
 * SYMBOL TABLE STRUCTURE (stack of scopes)
 * ============================================================ */
typedef struct {
    Scope* globalScope;
    Scope* currentScope;
} SymbolTable;

/* ============================================================
 * GLOBAL SYMBOL TABLE INSTANCE
 * ============================================================ */
extern SymbolTable symtab;

/* ============================================================
 * SYMBOL TABLE OPERATIONS
 * ============================================================ */

/* Scope management */
void initSymTab(void);
void enterScope(void);
void exitScope(void);

/* Declarations */
int addVar(char* name, char* type);
int addArray(const char* name, char* type, int size);
int addArray2D(const char* name, char* type, int rows, int cols);
int addParameter(char* name, char* type);
int addFunction(char* name, char* returnType, char** paramTypes, int paramCount);

/* Lookup and info retrieval */
Symbol* lookupSymbol(const char* name);
int isInCurrentScope(const char* name);
int getVarOffset(const char* name);
int getTotalStackBytes(void);
void getArray2DSizes(const char* name, int* rows, int* cols);

/* ============================================================
 * CONDITIONAL & LOOP VALIDATION
 * ============================================================ */

/**
 * Checks whether an expression type is valid for use
 * as a control condition (if / while).
 * Must evaluate to int, float, or bool.
 * Returns 1 if valid, 0 if invalid.
 */
int validateIfConditionType(const char* exprType);  /* Used for both IF and WHILE */

/**
 * Infers the type ("int", "float", "bool") of an expression node.
 * Used for semantic analysis and type checking.
 *
 * ------------------------------------------------------------
 *  Multiplication Support:
 *  ------------------------
 *   • If either operand is "float", the result is "float".
 *   • Otherwise, the result is "int".
 *   • "bool" operands are implicitly promoted to "int".
 * ------------------------------------------------------------
 */
const char* inferExprType(ASTNode* expr);

/* ============================================================
 * DEBUGGING UTILITIES
 * ============================================================ */
void printCurrentScope(void);
void printSymTab(void);

#endif /* SYMTAB_H */
