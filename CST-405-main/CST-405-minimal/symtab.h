#ifndef SYMTAB_H
#define SYMTAB_H

/* SYMBOL TABLE
 * Tracks all declared variables during compilation
 * Maps variable names to their memory locations (stack offsets)
 * Used for semantic checking and code generation
 */

#define MAX_VARS 10000  /* Maximum number of variables supported */

/* SYMBOL ENTRY - Information about each variable */
typedef struct {
    char* name;     /* Identifier */
    int offset;     /* Stack offset in bytes (from $sp) */
    int size;       /* Total size in bytes (scalars = 4, arrays = n*4) */
    int isArray;    /* 0 = scalar, 1 = 1D array, 2 = 2D array */
    int dim1;       /* For 1D: number of elements; for 2D: rows */
    int dim2;       /* For 2D arrays: columns, else 0 */
} Symbol;

/* SYMBOL TABLE STRUCTURE */
typedef struct {
    Symbol vars[MAX_VARS];  /* Array of all variables */
    int count;              /* Number of variables declared */
    int nextOffset;         /* Next available stack offset */
} SymbolTable;

/* SYMBOL TABLE OPERATIONS */
void initSymTab();               /* Initialize empty table */
int addVar(char* name);          /* Add scalar variable */
int addArray(const char* name, int size);          /* Add 1D array */
int addArray2D(const char* name, int rows, int cols); /* NEW: Add 2D array */

int getVarOffset(const char* name);    /* Get stack offset */
int isVarDeclared(const char* name);   /* Check if declared */

int getTotalStackBytes(void);          /* Compute total stack size */

/* OPTIONAL: debugging utilities */
void printSymTab();                    /* Display table */

/* OPTIONAL: array helpers (for semantic checks, etc.) */
int isArray(const char* name);         
int getArraySize(const char* name);    
void getArray2DSizes(const char* name, int* rows, int* cols);
#endif