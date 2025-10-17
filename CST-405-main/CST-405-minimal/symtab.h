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
void initSymTab();                       
void enterScope();                       
void exitScope();                        

int addVar(char* name, char* type);
int addArray(const char* name, char* type, int size);
int addArray2D(const char* name, char* type, int rows, int cols);

int addFunction(char* name, char* returnType, char** paramTypes, int paramCount);
int addParameter(char* name, char* type);

/* lookup / scope checks — now take const char* */
Symbol* lookupSymbol(const char* name);
int isInCurrentScope(const char* name);

int getVarOffset(const char* name);
int getTotalStackBytes(void);

/* helper for 2D array sizes */
void getArray2DSizes(const char* name, int* rows, int* cols);

void printCurrentScope();
void printSymTab();

#endif
