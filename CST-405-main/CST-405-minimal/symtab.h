#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>

#define MAX_VARS 10000

/* ============================================================
 * SYMBOL ENTRY
 * Represents variables, arrays, and functions.
 * ============================================================ */
typedef struct {
    char* name;         /* Identifier */
    char* type;         /* "int", "float", "void" */
    int offset;         /* Stack offset */
    int size;           /* Size in bytes (4 for int/float) */
    int isArray;        /* 0 = scalar, 1 = 1D array, 2 = 2D array */
    int dim1;           /* Rows / elements */
    int dim2;           /* Columns (for 2D) */

    /* Function metadata */
    int isFunction;     /* 1 if function */
    int paramCount;     /* Number of parameters */
    char** paramTypes;  /* Parameter types */

    /* Float tracking (NEW) */
    int isFloat;        /* 1 if this symbol is a float or float array */
} Symbol;

/* ============================================================
 * SCOPE STRUCTURE
 * Each scope maintains its own symbol table entries.
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

/* Debug printing */
void printCurrentScope(void);
void printSymTab(void);

#endif
