#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* Global symbol table */
SymbolTable symtab;

/* ============================================================
 * Helper: Create new scope
 * ============================================================ */
static Scope* createScope(Scope* parent) {
    Scope* s = malloc(sizeof(Scope));
    s->count = 0;
    s->nextOffset = 0;
    s->parent = parent;
    return s;
}

/* ============================================================
 * Initialize global scope
 * ============================================================ */
void initSymTab() {
    symtab.globalScope = createScope(NULL);
    symtab.currentScope = symtab.globalScope;
}

/* ============================================================
 * Enter a new scope (e.g., inside a function)
 * ============================================================ */
void enterScope() {
    Scope* newScope = createScope(symtab.currentScope);
    symtab.currentScope = newScope;
}

/* ============================================================
 * Exit current scope (return to parent)
 * ============================================================ */
void exitScope() {
    if (symtab.currentScope->parent != NULL) {
        Scope* old = symtab.currentScope;
        symtab.currentScope = old->parent;
        free(old);
    }
}

/* ============================================================
 * Add variable
 * ============================================================ */
int addVar(char* name, char* type) {
    Scope* s = symtab.currentScope;

    if (isInCurrentScope(name)) return -1;
    if (s->count >= MAX_VARS) {
        fprintf(stderr, "Error: scope full\n");
        exit(1);
    }

    Symbol* sym = &s->vars[s->count++];
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->offset = s->nextOffset;
    sym->size = 4;
    sym->isArray = 0;
    sym->isFunction = 0;
    s->nextOffset += 4;

    return sym->offset;
}

/* ============================================================
 * Add 1D Array
 * ============================================================ */
int addArray(const char* name, char* type, int size) {
    Scope* s = symtab.currentScope;
    if (isInCurrentScope(name)) return -1;

    Symbol* sym = &s->vars[s->count++];
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->isArray = 1;
    sym->dim1 = size;
    sym->dim2 = 0;
    sym->size = size * 4;
    sym->offset = s->nextOffset;
    sym->isFunction = 0;

    s->nextOffset += sym->size;
    return sym->offset;
}

/* ============================================================
 * Add 2D Array
 * ============================================================ */
int addArray2D(const char* name, char* type, int rows, int cols) {
    Scope* s = symtab.currentScope;
    if (isInCurrentScope(name)) return -1;

    Symbol* sym = &s->vars[s->count++];
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->isArray = 2;
    sym->dim1 = rows;
    sym->dim2 = cols;
    sym->size = rows * cols * 4;
    sym->offset = s->nextOffset;
    sym->isFunction = 0;

    s->nextOffset += sym->size;
    return sym->offset;
}

/* ============================================================
 * Add function
 * ============================================================ */
int addFunction(char* name, char* returnType, char** paramTypes, int paramCount) {
    Scope* global = symtab.globalScope;
    if (isInCurrentScope(name)) return -1;

    Symbol* sym = &global->vars[global->count++];
    sym->name = strdup(name);
    sym->type = strdup(returnType);
    sym->isFunction = 1;
    sym->paramCount = paramCount;

    if (paramCount > 0) {
        sym->paramTypes = malloc(paramCount * sizeof(char*));
        for (int i = 0; i < paramCount; i++) {
            sym->paramTypes[i] = strdup(paramTypes[i]);
        }
    } else {
        sym->paramTypes = NULL;
    }

    return 0;
}

/* ============================================================
 * Add function parameter (local to current function scope)
 * ============================================================ */
int addParameter(char* name, char* type) {
    return addVar(name, type);
}

/* ============================================================
 * Lookup symbol (search upward through parent scopes)
 * ============================================================ */
Symbol* lookupSymbol(const char* name) {
    Scope* s = symtab.currentScope;
    while (s) {
        for (int i = 0; i < s->count; i++) {
            if (strcmp(s->vars[i].name, name) == 0) {
                return &s->vars[i];
            }
        }
        s = s->parent;
    }
    return NULL;
}

/* ============================================================
 * Check if a symbol exists in the current scope
 * ============================================================ */
int isInCurrentScope(const char* name) {
    Scope* s = symtab.currentScope;
    for (int i = 0; i < s->count; i++) {
        if (strcmp(s->vars[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

/* ============================================================
 * Get variable offset
 * ============================================================ */
int getVarOffset(const char* name) {
    Symbol* sym = lookupSymbol(name);
    return sym ? sym->offset : -1;
}

/* ============================================================
 * Get rows and cols for a 2D array
 * ============================================================ */
void getArray2DSizes(const char* name, int* rows, int* cols) {
    Symbol* sym = lookupSymbol(name);
    if (!sym || sym->isArray != 2) {
        fprintf(stderr, "Error: %s is not declared as a 2D array\n", name);
        *rows = *cols = 0;
        return;
    }
    *rows = sym->dim1;
    *cols = sym->dim2;
}

/* ============================================================
 * Get total stack bytes for current scope
 * ============================================================ */
int getTotalStackBytes(void) {
    return symtab.currentScope->nextOffset;
}

/* ============================================================
 * Print current scope
 * ============================================================ */
void printCurrentScope() {
    Scope* s = symtab.currentScope;
    printf("\n=== CURRENT SCOPE ===\n");
    for (int i = 0; i < s->count; i++) {
        Symbol* sym = &s->vars[i];
        printf("[%d] %s (%s)", i, sym->name, sym->type);
        if (sym->isFunction)
            printf(" [FUNC, params=%d]\n", sym->paramCount);
        else if (sym->isArray == 1)
            printf(" [ARRAY1D size=%d]\n", sym->dim1);
        else if (sym->isArray == 2)
            printf(" [ARRAY2D %dx%d]\n", sym->dim1, sym->dim2);
        else
            printf(" [VAR offset=%d]\n", sym->offset);
    }
    printf("=====================\n");
}

/* ============================================================
 * Print entire symbol table (global + nested scopes)
 * ============================================================ */
void printSymTab() {
    printf("\n=== SYMBOL TABLE (All Scopes) ===\n");
    Scope* s = symtab.currentScope;
    int level = 0;
    while (s) {
        printf("-- Scope Level %d --\n", level++);
        for (int i = 0; i < s->count; i++) {
            Symbol* sym = &s->vars[i];
            printf("%s : %s\n", sym->name, sym->type);
        }
        s = s->parent;
    }
    printf("===============================\n");
}
