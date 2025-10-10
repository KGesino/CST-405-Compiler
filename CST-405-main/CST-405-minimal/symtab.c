/* SYMBOL TABLE IMPLEMENTATION
 * Manages variable and array declarations and lookups
 * Provides memory layout information for code generation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* Global symbol table instance */
SymbolTable symtab;

/* Initialize an empty symbol table */
void initSymTab() {
    symtab.count = 0;
    symtab.nextOffset = 0;
}

/* Add a new scalar variable */
int addVar(char* name) {
    if (isVarDeclared(name)) {
        return -1;  /* Already declared */
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table full (MAX_VARS=%d)\n", MAX_VARS);
        exit(1);
    }

    Symbol* s = &symtab.vars[symtab.count];
    s->name = strdup(name);
    s->offset = symtab.nextOffset;
    s->size = 4;
    s->isArray = 0;
    s->dim1 = 0;
    s->dim2 = 0;

    symtab.nextOffset += 4;
    symtab.count++;
    return s->offset;
}

/* Add a 1D array: reserves size * 4 bytes */
int addArray(const char* name, int size) {
    if (size <= 0) {
        fprintf(stderr, "Error: array '%s' has invalid size %d\n", name, size);
        return -1;
    }
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table full (MAX_VARS=%d)\n", MAX_VARS);
        exit(1);
    }

    Symbol* s = &symtab.vars[symtab.count];
    s->name = strdup(name);
    s->offset = symtab.nextOffset;
    s->isArray = 1;
    s->dim1 = size;
    s->dim2 = 0;
    s->size = size * 4;

    symtab.nextOffset += s->size;
    symtab.count++;
    return s->offset;
}

/* ===== NEW: Add a 2D array ===== */
int addArray2D(const char* name, int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        fprintf(stderr, "Error: array '%s' has invalid size %dx%d\n", name, rows, cols);
        return -1;
    }
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table full (MAX_VARS=%d)\n", MAX_VARS);
        exit(1);
    }

    Symbol* s = &symtab.vars[symtab.count];
    s->name = strdup(name);
    s->offset = symtab.nextOffset;
    s->isArray = 2;
    s->dim1 = rows;
    s->dim2 = cols;
    s->size = rows * cols * 4;

    symtab.nextOffset += s->size;
    symtab.count++;
    return s->offset;
}
/* ================================= */

/* ✅ FIXED: Added const to match symtab.h */
int getVarOffset(const char* name) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0) {
            return symtab.vars[i].offset;
        }
    }
    return -1;
}

/* ✅ FIXED: Added const to match symtab.h */
int isVarDeclared(const char* name) {
    return getVarOffset(name) != -1;
}

/* Get total bytes required for the stack frame */
int getTotalStackBytes(void) {
    return symtab.nextOffset;
}

/* ===== OPTIONAL array helpers ===== */
int isArray(const char* name) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0) {
            return symtab.vars[i].isArray;
        }
    }
    return 0;
}

int getArraySize(const char* name) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0 && symtab.vars[i].isArray == 1) {
            return symtab.vars[i].dim1;
        }
    }
    return -1;
}

void getArray2DSizes(const char* name, int* rows, int* cols) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0 && symtab.vars[i].isArray == 2) {
            *rows = symtab.vars[i].dim1;
            *cols = symtab.vars[i].dim2;
            return;
        }
    }
    *rows = *cols = -1;
}
/* ================================= */

/* Print current symbol table (debug) */
void printSymTab() {
    printf("\n=== SYMBOL TABLE STATE ===\n");
    printf("Count: %d, Next Offset: %d\n", symtab.count, symtab.nextOffset);
    if (symtab.count == 0) {
        printf("(empty)\n");
    } else {
        printf("Symbols:\n");
        for (int i = 0; i < symtab.count; i++) {
            Symbol* s = &symtab.vars[i];
            if (s->isArray == 0)
                printf("  [%d] VAR  %s -> offset %d, size %d\n", i, s->name, s->offset, s->size);
            else if (s->isArray == 1)
                printf("  [%d] ARRAY1D %s[%d] -> offset %d, bytes %d\n",
                       i, s->name, s->dim1, s->offset, s->size);
            else
                printf("  [%d] ARRAY2D %s[%d][%d] -> offset %d, bytes %d\n",
                       i, s->name, s->dim1, s->dim2, s->offset, s->size);
        }
    }
    printf("==========================\n\n");
}
