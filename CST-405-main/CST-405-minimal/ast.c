#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* Integer literal node */
ASTNode* createNum(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_NUM;
    node->data.num = value;
    return node;
}

/* Float literal node (NEW) */
ASTNode* createFloatNode(float value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FLOAT;
    node->data.fnum = value;
    return node;
}

/* Variable node */
ASTNode* createVar(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR;
    node->data.name = strdup(name);
    return node;
}

/* Binary operation node */
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BINOP;
    node->data.binop.op = op;
    node->data.binop.left = left;
    node->data.binop.right = right;
    return node;
}

/* Variable declaration */
ASTNode* createDecl(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_DECL;
    node->data.name = strdup(name);
    return node;
}

/* Multi-declaration support */
ASTNode* createDeclList(ASTNode* list, ASTNode* decl) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STMT_LIST;
    node->data.stmtlist.stmt = list;
    node->data.stmtlist.next = decl;
    return node;
}

/* Assignment */
ASTNode* createAssign(char* var, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->data.assign.var = strdup(var);
    node->data.assign.value = value;
    return node;
}

/* Print statement */
ASTNode* createPrint(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->data.expr = expr;
    return node;
}

/* Statement list */
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STMT_LIST;
    node->data.stmtlist.stmt = stmt1;
    node->data.stmtlist.next = stmt2;
    return node;
}

/* Array declaration */
ASTNode* createArrayDecl(char* name, int size) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_DECL;
    node->data.arrdecl.name = strdup(name);
    node->data.arrdecl.size = size;
    return node;
}

/* Array assignment */
ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ASSIGN;
    node->data.arrassign.var = strdup(name);
    node->data.arrassign.index = index;
    node->data.arrassign.value = value;
    return node;
}

/* Array access */
ASTNode* createArrayAccess(char* name, ASTNode* index) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ACCESS;
    node->data.arraccess.name = strdup(name);
    node->data.arraccess.index = index;
    return node;
}

/* 2D Array declaration */
ASTNode* createArray2DDecl(char* name, int rows, int cols) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY2D_DECL;
    node->data.arr2d_decl.name = strdup(name);
    node->data.arr2d_decl.rows = rows;
    node->data.arr2d_decl.cols = cols;
    return node;
}

/* 2D Array assignment */
ASTNode* createArray2DAssign(char* name, ASTNode* row, ASTNode* col, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY2D_ASSIGN;
    node->data.arr2d_assign.var = strdup(name);
    node->data.arr2d_assign.row = row;
    node->data.arr2d_assign.col = col;
    node->data.arr2d_assign.value = value;
    return node;
}

/* 2D Array access */
ASTNode* createArray2DAccess(char* name, ASTNode* row, ASTNode* col) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY2D_ACCESS;
    node->data.arr2d_access.name = strdup(name);
    node->data.arr2d_access.row = row;
    node->data.arr2d_access.col = col;
    return node;
}

/* Function declaration */
ASTNode* createFuncDecl(char* returnType, char* name, ASTNode* params, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNC_DECL;
    node->data.func_decl.returnType = strdup(returnType);
    node->data.func_decl.name = strdup(name);
    node->data.func_decl.params = params;
    node->data.func_decl.body = body;
    return node;
}

/* Function call */
ASTNode* createFuncCall(char* name, ASTNode* args) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNC_CALL;
    node->data.func_call.name = strdup(name);
    node->data.func_call.args = args;
    return node;
}

/* Parameter */
ASTNode* createParam(char* type, char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM;
    node->data.param.type = strdup(type);
    node->data.param.name = strdup(name);
    return node;
}

/* Parameter list */
ASTNode* createParamList(ASTNode* param, ASTNode* next) {
    // ✅ FIX: if both are NULL, this is an empty param list
    if (!param && !next)
        return NULL;

    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM_LIST;
    node->data.list.item = param;
    node->data.list.next = next;
    return node;
}

/* Argument list */
ASTNode* createArgList(ASTNode* arg, ASTNode* next) {
    if (!arg && !next)
        return NULL;

    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARG_LIST;
    node->data.list.item = arg;
    node->data.list.next = next;
    return node;
}

/* Return statement */
ASTNode* createReturn(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->data.return_expr = expr;
    return node;
}

/* Function list */
ASTNode* createFuncList(ASTNode* func, ASTNode* next) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNC_LIST;
    node->data.list.item = func;
    node->data.list.next = next;
    return node;
}

/* Block */
ASTNode* createBlock(ASTNode* stmts) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BLOCK;
    node->data.expr = stmts;
    return node;
}

/* Print the AST (includes float support) */
void printAST(ASTNode* node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) printf("  ");

    switch (node->type) {
        case NODE_NUM:
            printf("NUM: %d\n", node->data.num);
            break;
        case NODE_FLOAT:
            printf("FLOAT: %.6f\n", node->data.fnum);
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
            printAST(node->data.stmtlist.stmt, level);
            printAST(node->data.stmtlist.next, level);
            break;
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
        case NODE_ARRAY2D_DECL:
            printf("ARRAY2D_DECL: %s[%d][%d]\n",
                   node->data.arr2d_decl.name,
                   node->data.arr2d_decl.rows,
                   node->data.arr2d_decl.cols);
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
        case NODE_FUNC_DECL:
            printf("FUNC_DECL: %s %s()\n", node->data.func_decl.returnType, node->data.func_decl.name);
            if (node->data.func_decl.params) {
                printf("%*sParams:\n", level * 2, "");
                printAST(node->data.func_decl.params, level + 1);
            }
            printf("%*sBody:\n", level * 2, "");
            printAST(node->data.func_decl.body, level + 1);
            break;
        case NODE_FUNC_CALL:
            printf("FUNC_CALL: %s()\n", node->data.func_call.name);
            printAST(node->data.func_call.args, level + 1);
            break;
        case NODE_PARAM:
            printf("PARAM: %s %s\n", node->data.param.type, node->data.param.name);
            break;
        case NODE_PARAM_LIST:
        case NODE_ARG_LIST:
        case NODE_FUNC_LIST:
            printAST(node->data.list.item, level);
            printAST(node->data.list.next, level);
            break;
        case NODE_RETURN:
            printf("RETURN\n");
            printAST(node->data.return_expr, level + 1);
            break;
        case NODE_BLOCK:
            printf("BLOCK\n");
            printAST(node->data.expr, level + 1);
            break;
        default:
            printf("UNKNOWN NODE TYPE %d\n", node->type);
            break;
    }
}
