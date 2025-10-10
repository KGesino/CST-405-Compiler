#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>

#define MAX_VARS 10000

/* ============================================================
 * SYMBOL ENTRY
 * Represents a variable OR a function.
 * ============================================================ */
typedef struct {
    char* name;         /* Identifier */
    char* type;         /* Variable type or function return type */
    int offset;         /* Stack offset */
    int size;           /* Size in bytes */
    int isArray;        /* 0 = scalar, 1 = 1D array, 2 = 2D array */
    int dim1;           /* Rows / elements */
    int dim2;           /* Columns (for 2D) */

    /* Function metadata */
    int isFunction;     /* 1 if function */
    int paramCount;     /* Number of parameters */
    char** paramTypes;  /* Parameter types */
} Symbol;

/* ============================================================
 * SCOPE STRUCTURE
 * Each scope contains its own variable/function entries.
 * ============================================================ */
typedef struct Scope {
    Symbol vars[MAX_VARS];
    int count;
    int nextOffset;
    struct Scope* parent;  /* Link to outer scope */
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
void initSymTab();                       /* Initialize global scope */
void enterScope();                       /* Enter new function/scope */
void exitScope();                        /* Exit current scope */

int addVar(char* name, char* type);      /* Add scalar variable */
int addArray(const char* name, char* type, int size);
int addArray2D(const char* name, char* type, int rows, int cols);

int addFunction(char* name, char* returnType, char** paramTypes, int paramCount);
int addParameter(char* name, char* type);

Symbol* lookupSymbol(char* name);        /* Search through scopes */
int isInCurrentScope(char* name);        /* Check only current scope */

int getVarOffset(const char* name);
int getTotalStackBytes(void);

void printCurrentScope();
void printSymTab();                      /* Print entire table (all scopes) */

#endif
