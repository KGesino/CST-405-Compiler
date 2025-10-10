/* AST IMPLEMENTATION
 * Functions to create and manipulate Abstract Syntax Tree nodes
 * The AST is built during parsing and used for all subsequent phases
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* Create a number literal node */
ASTNode* createNum(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_NUM;
    node->data.num = value;  /* Store the integer value */
    return node;
}

/* Create a variable reference node */
ASTNode* createVar(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR;
    node->data.name = strdup(name);  /* Copy the variable name */
    return node;
}

/* Create a binary operation node (for addition and subtraction) */
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BINOP;
    node->data.binop.op = op;        /* Store operator (+,-) */
    node->data.binop.left = left;    /* Left subtree */
    node->data.binop.right = right;  /* Right subtree */
    return node;
}

/* Create a variable declaration node */
ASTNode* createDecl(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_DECL;
    node->data.name = strdup(name);  /* Store variable name */
    return node;
}

/*
ASTNode* createDeclWithAssgn(char* name, int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_DECL;
    node->data.value = value; 
    return node;
}
*/

/* Create an assignment statement node */
ASTNode* createAssign(char* var, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->data.assign.var = strdup(var);  /* Variable name */
    node->data.assign.value = value;      /* Expression tree */
    return node;
}

/* Create a print statement node */
ASTNode* createPrint(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->data.expr = expr;  /* Expression to print */
    return node;
}

/* Create a statement list node (links statements together) */
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STMT_LIST;
    node->data.stmtlist.stmt = stmt1;  /* First statement */
    node->data.stmtlist.next = stmt2;  /* Rest of list */
    return node;
}

/* ======== array constructors ======== */

/* Array declaration: int a[SIZE]; */
ASTNode* createArrayDecl(char* name, int size) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_DECL;
    node->data.arrdecl.name = strdup(name);
    node->data.arrdecl.size = size;
    return node;
}

/* Array element assignment: a[index] = value; */
ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ASSIGN;
    node->data.arrassign.var = strdup(name);
    node->data.arrassign.index = index;
    node->data.arrassign.value = value;
    return node;
}

/* Array access expression: a[index] */
ASTNode* createArrayAccess(char* name, ASTNode* index) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ACCESS;
    node->data.arraccess.name = strdup(name);
    node->data.arraccess.index = index;
    return node;
}

/* ======== NEW: 2D array constructors ======== */

/* 2D array declaration: int a[rows][cols]; */
ASTNode* createArray2DDecl(char* name, int rows, int cols) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY2D_DECL;
    node->data.arr2d_decl.name = strdup(name);
    node->data.arr2d_decl.rows = rows;
    node->data.arr2d_decl.cols = cols;
    return node;
}

/* 2D array assignment: a[i][j] = value; */
ASTNode* createArray2DAssign(char* name, ASTNode* row, ASTNode* col, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY2D_ASSIGN;
    node->data.arr2d_assign.var = strdup(name);
    node->data.arr2d_assign.row = row;
    node->data.arr2d_assign.col = col;
    node->data.arr2d_assign.value = value;
    return node;
}

/* 2D array access: a[i][j] */
ASTNode* createArray2DAccess(char* name, ASTNode* row, ASTNode* col) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY2D_ACCESS;
    node->data.arr2d_access.name = strdup(name);
    node->data.arr2d_access.row = row;
    node->data.arr2d_access.col = col;
    return node;
}


/* Display the AST structure (for debugging and education) */
void printAST(ASTNode* node, int level) {
    if (!node) return;
    
    /* Indent based on tree depth */
    for (int i = 0; i < level; i++) printf("  ");
    
    /* Print node based on its type */
    switch(node->type) {
        case NODE_NUM:
            printf("NUM: %d\n", node->data.num);
            break;
        case NODE_VAR:
            printf("VAR: %s\n", node->data.name);
            break;
        case NODE_BINOP:
            printf("BINOP: %c\n", node->data.binop.op);
            printAST(node->data.binop.left, level + 1);
            printAST(node->data.binop.right, level + 1);
            break;
        case NODE_DECL:
            printf("DECL: %s\n", node->data.name);
            break;
        case NODE_ASSIGN:
            printf("ASSIGN: %s\n", node->data.assign.var);
            printAST(node->data.assign.value, level + 1);
            break;
        case NODE_PRINT:
            printf("PRINT\n");
            printAST(node->data.expr, level + 1);
            break;
        case NODE_STMT_LIST:
            /* Print statements in sequence at same level */
            printAST(node->data.stmtlist.stmt, level);
            printAST(node->data.stmtlist.next, level);
            break;
        /* ======== NEW: array cases ======== */
        case NODE_ARRAY_DECL:
            printf("ARRAY_DECL: %s[%d]\n", node->data.arrdecl.name, node->data.arrdecl.size);
            break;
        case NODE_ARRAY_ASSIGN:
            printf("ARRAY_ASSIGN: %s[...]\n", node->data.arrassign.var);
            printAST(node->data.arrassign.index, level + 1);
            printAST(node->data.arrassign.value, level + 1);
            break;
        case NODE_ARRAY_ACCESS:
            printf("ARRAY_ACCESS: %s[...]\n", node->data.arraccess.name);
            printAST(node->data.arraccess.index, level + 1);
            break;
        /* ================================== */

        /* ======== NEW: 2D arrays ======== */
        case NODE_ARRAY2D_DECL:
            printf("ARRAY2D_DECL: %s[%d][%d]\n", node->data.arr2d_decl.name,
                   node->data.arr2d_decl.rows, node->data.arr2d_decl.cols);
            break;
        case NODE_ARRAY2D_ASSIGN:
            printf("ARRAY2D_ASSIGN: %s[...][...]\n", node->data.arr2d_assign.var);
            printAST(node->data.arr2d_assign.row, level + 1);
            printAST(node->data.arr2d_assign.col, level + 1);
            printAST(node->data.arr2d_assign.value, level + 1);
            break;
        case NODE_ARRAY2D_ACCESS:
            printf("ARRAY2D_ACCESS: %s[...][...]\n", node->data.arr2d_access.name);
            printAST(node->data.arr2d_access.row, level + 1);
            printAST(node->data.arr2d_access.col, level + 1);
            break;
        default:
            printf("UNKNOWN NODE TYPE %d\n", node->type);
            break;
    }
}