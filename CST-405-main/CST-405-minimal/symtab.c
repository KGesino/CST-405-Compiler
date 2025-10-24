#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* ============================================================
 * Global symbol table
 * ============================================================ */
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
void initSymTab(void) {
    symtab.globalScope = createScope(NULL);
    symtab.currentScope = symtab.globalScope;
}

/* ============================================================
 * Enter / exit scope
 * ============================================================ */
void enterScope(void) {
    Scope* newScope = createScope(symtab.currentScope);
    symtab.currentScope = newScope;
}

void exitScope(void) {
    if (symtab.currentScope->parent) {
        Scope* old = symtab.currentScope;
        symtab.currentScope = old->parent;
        free(old);
    }
}

/* ============================================================
 * Internal: mark float/int
 * ============================================================ */
static int isFloatType(const char* type) {
    return (type && strcmp(type, "float") == 0);
}

/* ============================================================
 * Add variable
 * ============================================================ */
int addVar(char* name, char* type) {

    // -------- FIX: sanity guard so we don't blow up later --------
    if (!name || !type) {
        // silently ignore invalid entries; return -1 so caller knows it wasn't added
        // you could also fprintf(stderr, ...) here if you want debug noise
        return -1; // <-- FIX
    }

    Scope* s = symtab.currentScope;

    if (isInCurrentScope(name)) return -1;
    if (s->count >= MAX_VARS) {
        fprintf(stderr, "Error: scope full\n");
        exit(1);
    }

    Symbol* sym = &s->vars[s->count++];
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->isFloat = isFloatType(type);
    sym->offset = s->nextOffset;
    sym->size = 4;
    sym->isArray = 0;
    sym->isFunction = 0;
    sym->dim1 = 0;
    sym->dim2 = 0;
    sym->paramCount = 0;
    sym->paramTypes = NULL;

    s->nextOffset += 4;
    return sym->offset;
}

/* ============================================================
 * Add 1D Array
 * ============================================================ */
int addArray(const char* name, char* type, int size) {

    if (!name || !type) {          // <-- FIX
        return -1;
    }

    Scope* s = symtab.currentScope;
    if (isInCurrentScope(name)) return -1;

    if (s->count >= MAX_VARS) {
        fprintf(stderr, "Error: scope full\n");
        exit(1);
    }

    Symbol* sym = &s->vars[s->count++];
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->isFloat = isFloatType(type);
    sym->isArray = 1;
    sym->dim1 = size;
    sym->dim2 = 0;
    sym->size = size * 4;
    sym->offset = s->nextOffset;
    sym->isFunction = 0;
    sym->paramCount = 0;
    sym->paramTypes = NULL;

    s->nextOffset += sym->size;
    return sym->offset;
}

/* ============================================================
 * Add 2D Array
 * ============================================================ */
int addArray2D(const char* name, char* type, int rows, int cols) {

    if (!name || !type) {          // <-- FIX
        return -1;
    }

    Scope* s = symtab.currentScope;
    if (isInCurrentScope(name)) return -1;

    if (s->count >= MAX_VARS) {
        fprintf(stderr, "Error: scope full\n");
        exit(1);
    }

    Symbol* sym = &s->vars[s->count++];
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->isFloat = isFloatType(type);
    sym->isArray = 2;
    sym->dim1 = rows;
    sym->dim2 = cols;
    sym->size = rows * cols * 4;
    sym->offset = s->nextOffset;
    sym->isFunction = 0;
    sym->paramCount = 0;
    sym->paramTypes = NULL;

    s->nextOffset += sym->size;
    return sym->offset;
}

/* ============================================================
 * Add function
 * ============================================================ */
int addFunction(char* name, char* returnType, char** paramTypes, int paramCount) {

    if (!name || !returnType) {    // <-- FIX
        return -1;
    }

    Scope* global = symtab.globalScope;
    if (isInCurrentScope(name)) return -1;

    if (global->count >= MAX_VARS) {
        fprintf(stderr, "Error: global scope full\n");
        exit(1);
    }

    Symbol* sym = &global->vars[global->count++];
    sym->name = strdup(name);
    sym->type = strdup(returnType);
    sym->isFloat = isFloatType(returnType);
    sym->isFunction = 1;
    sym->isArray = 0;
    sym->dim1 = 0;
    sym->dim2 = 0;
    sym->offset = 0;  // often ignored for functions
    sym->size = 0;
    sym->paramCount = paramCount;

    if (paramCount > 0 && paramTypes) {
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
 * Add function parameter
 * ============================================================ */
int addParameter(char* name, char* type) {
    // This just delegates to addVar, which now has NULL guards
    return addVar(name, type);
}

/* ============================================================
 * Lookup and scope utilities
 * ============================================================ */
Symbol* lookupSymbol(const char* name) {

    if (!name) {                   // <-- FIX
        return NULL;
    }

    Scope* s = symtab.currentScope;
    while (s) {
        for (int i = 0; i < s->count; i++) {
            if (s->vars[i].name && strcmp(s->vars[i].name, name) == 0) { // <-- FIX
                return &s->vars[i];
            }
        }
        s = s->parent;
    }
    return NULL;
}

int isInCurrentScope(const char* name) {

    if (!name) {                   // <-- FIX
        return 0;
    }

    Scope* s = symtab.currentScope;
    for (int i = 0; i < s->count; i++) {
        if (s->vars[i].name && strcmp(s->vars[i].name, name) == 0) { // <-- FIX
            return 1;
        }
    }
    return 0;
}

int getVarOffset(const char* name) {
    Symbol* sym = lookupSymbol(name);
    return sym ? sym->offset : -1;
}

/* ============================================================
 * Get rows and cols for 2D array
 * ============================================================ */
void getArray2DSizes(const char* name, int* rows, int* cols) {
    Symbol* sym = lookupSymbol(name);
    if (!sym || sym->isArray != 2) {
        fprintf(stderr, "Error: %s is not declared as a 2D array\n", name ? name : "(null)"); // <-- FIX
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
void printCurrentScope(void) {
    Scope* s = symtab.currentScope;
    printf("\n=== CURRENT SCOPE ===\n");
    for (int i = 0; i < s->count; i++) {
        Symbol* sym = &s->vars[i];
        printf("[%d] %s (%s)", i,
               sym->name ? sym->name : "(null)",          // <-- FIX
               sym->type ? sym->type : "(null)");          // <-- FIX
        if (sym->isFunction)
            printf(" [FUNC, params=%d]\n", sym->paramCount);
        else if (sym->isArray == 1)
            printf(" [ARRAY1D size=%d]\n", sym->dim1);
        else if (sym->isArray == 2)
            printf(" [ARRAY2D %dx%d]\n", sym->dim1, sym->dim2);
        else if (sym->isFloat)
            printf(" [FLOAT var offset=%d]\n", sym->offset);
        else
            printf(" [VAR offset=%d]\n", sym->offset);
    }
    printf("=====================\n");
}

/* ============================================================
 * Print full symbol table
 * ============================================================ */
void printSymTab(void) {
    printf("\n=== SYMBOL TABLE (All Scopes) ===\n");
    Scope* s = symtab.currentScope;
    int level = 0;
    while (s) {
        printf("-- Scope Level %d --\n", level++);
        for (int i = 0; i < s->count; i++) {
            Symbol* sym = &s->vars[i];
            printf("%s : %s",
                   sym->name ? sym->name : "(null)",       // <-- FIX
                   sym->type ? sym->type : "(null)");       // <-- FIX
            if (sym->isFunction)
                printf(" (function, params=%d)", sym->paramCount);
            if (sym->isFloat)
                printf(" [float]");
            printf("\n");
        }
        s = s->parent;
    }
    printf("===============================\n");
}
