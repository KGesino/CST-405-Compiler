#ifndef AST_H
#define AST_H

/* ABSTRACT SYNTAX TREE (AST)
 * Represents the hierarchical structure of source code
 */

typedef enum {
    NODE_NUM,
    NODE_FLOAT,          /* NEW: float literal node */
    NODE_VAR,
    NODE_BINOP,
    NODE_DECL,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_STMT_LIST,
    NODE_ARRAY_DECL,
    NODE_ARRAY_ASSIGN,
    NODE_ARRAY_ACCESS,
    NODE_ARRAY2D_DECL,
    NODE_ARRAY2D_ASSIGN,
    NODE_ARRAY2D_ACCESS,

    NODE_FUNC_DECL,
    NODE_FUNC_CALL,
    NODE_PARAM,
    NODE_PARAM_LIST,
    NODE_ARG_LIST,
    NODE_RETURN,
    NODE_FUNC_LIST,
    NODE_BLOCK
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        int num;
        float fnum;        /* NEW: float literal value */
        char* name;

        struct {
            char op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binop;

        struct {
            char* var;
            struct ASTNode* value;
        } assign;

        struct ASTNode* expr;

        struct {
            struct ASTNode* stmt;
            struct ASTNode* next;
        } stmtlist;

        struct {
            char* name;
            int size;
        } arrdecl;

        struct {
            char* var;
            struct ASTNode* index;
            struct ASTNode* value;
        } arrassign;

        struct {
            char* name;
            struct ASTNode* index;
        } arraccess;

        struct {
            char* name;
            int rows;
            int cols;
        } arr2d_decl;

        struct {
            char* var;
            struct ASTNode* row;
            struct ASTNode* col;
            struct ASTNode* value;
        } arr2d_assign;

        struct {
            char* name;
            struct ASTNode* row;
            struct ASTNode* col;
        } arr2d_access;

        struct {
            char* returnType;
            char* name;
            struct ASTNode* params;
            struct ASTNode* body;
        } func_decl;

        struct {
            char* name;
            struct ASTNode* args;
        } func_call;

        struct {
            char* type;
            char* name;
        } param;

        struct {
            struct ASTNode* item;
            struct ASTNode* next;
        } list;

        struct ASTNode* return_expr;
    } data;

} ASTNode;

/* Constructors */
ASTNode* createNum(int value);
ASTNode* createFloatNode(float value); /* NEW */
ASTNode* createVar(char* name);
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right);
ASTNode* createDecl(char* name);
ASTNode* createDeclList(ASTNode* list, ASTNode* decl);
ASTNode* createAssign(char* var, ASTNode* value);
ASTNode* createPrint(ASTNode* expr);
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2);
ASTNode* createArrayDecl(char* name, int size);
ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value);
ASTNode* createArrayAccess(char* name, ASTNode* index);
ASTNode* createArray2DDecl(char* name, int rows, int cols);
ASTNode* createArray2DAssign(char* name, ASTNode* row, ASTNode* col, ASTNode* value);
ASTNode* createArray2DAccess(char* name, ASTNode* row, ASTNode* col);

ASTNode* createFuncDecl(char* returnType, char* name, ASTNode* params, ASTNode* body);
ASTNode* createFuncCall(char* name, ASTNode* args);
ASTNode* createParam(char* type, char* name);
ASTNode* createParamList(ASTNode* param, ASTNode* next);
ASTNode* createArgList(ASTNode* arg, ASTNode* next);
ASTNode* createReturn(ASTNode* expr);
ASTNode* createFuncList(ASTNode* func, ASTNode* next);
ASTNode* createBlock(ASTNode* stmts);

void printAST(ASTNode* node, int level);

#endif
