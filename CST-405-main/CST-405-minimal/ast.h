#ifndef AST_H
#define AST_H

#include "parser.tab.h"

/* ============================================================
 * ABSTRACT SYNTAX TREE (AST)
 * Represents the hierarchical structure of source code
 * ============================================================ */

typedef enum {
    NODE_NUM,
    NODE_FLOAT,          /* float literal node */
    NODE_BOOL,           /* boolean literal node */
    NODE_CHAR,           /* ✅ NEW: character literal node */
    NODE_VAR,
    NODE_BINOP,
    NODE_UNOP,           /* unary operator node (e.g., NOT) */
    NODE_DECL,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_WRITE,          /* ✅ NEW: write(expr); */
    NODE_WRITELN,        /* ✅ NEW: writeln; */
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
    NODE_BLOCK,
    NODE_IF,
    NODE_WHILE,
    NODE_RACE
} NodeType;

/* ============================================================
 * BINARY OPERATOR ENUM
 * ============================================================ */
typedef enum {
    OP_ADD = '+',
    OP_SUB = '-',
    OP_MUL = '*',
    OP_DIV = '/',
    OP_GT  = '>',
    OP_LT  = '<',
    OP_GE  = 'G',
    OP_LE  = 'L',
    OP_EQ  = 'E',
    OP_NE  = 'N',
    OP_AND = '&',
    OP_OR  = '|'
} BinOpType;

/* ============================================================
 * AST NODE STRUCTURE
 * ============================================================ */
typedef struct ASTNode {
    NodeType type;
    union {
        int num;
        float fnum;
        int boolval;
        int ch;             /* ✅ NEW: for character literals */
        char* name;

        /* ---------------- Unary operation ---------------- */
        struct {
            int op;
            struct ASTNode* expr;
        } unop;

        /* ---------------- Binary operation ---------------- */
        struct {
            int op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binop;

        /* ---------------- Assignments ---------------- */
        struct {
            char* var;
            struct ASTNode* value;
        } assign;

        struct ASTNode* expr;

        /* ---------------- Statement list ---------------- */
        struct {
            struct ASTNode* stmt;
            struct ASTNode* next;
        } stmtlist;

        /* ---------------- Arrays ---------------- */
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

        /* ---------------- Functions ---------------- */
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

        /* ---------------- Parameters and Lists ---------------- */
        struct {
            char* type;
            char* name;
        } param;

        struct {
            struct ASTNode* item;
            struct ASTNode* next;
        } list;

        struct ASTNode* return_expr;

        /* ---------------- If statement ---------------- */
        struct {
            struct ASTNode* condition;
            struct ASTNode* thenBranch;
            struct ASTNode* elseBranch;
        } ifstmt;

        /* ---------------- While statement ---------------- */
        struct {
            struct ASTNode* condition;
            struct ASTNode* body;
        } whilestmt;

        /* ---------------- Race statement ---------------- */
        struct {
            struct ASTNode* left;
            struct ASTNode* right;
        } racestmt;

    } data;

} ASTNode;

/* ============================================================
 * CONSTRUCTORS
 * ============================================================ */
ASTNode* createNum(int value);
ASTNode* createFloatNode(float value);
ASTNode* createBoolNode(int value);
ASTNode* createCharNode(int ch);                 /* ✅ NEW */
ASTNode* createVar(char* name);
ASTNode* createBinOp(int op, ASTNode* left, ASTNode* right);
ASTNode* createUnaryOp(int op, ASTNode* expr);
ASTNode* createDecl(char* name);
ASTNode* createDeclList(ASTNode* list, ASTNode* decl);
ASTNode* createAssign(char* var, ASTNode* value);
ASTNode* createPrint(ASTNode* expr);
ASTNode* createWrite(ASTNode* expr);             /* ✅ NEW */
ASTNode* createWriteln(void);                    /* ✅ NEW */
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

ASTNode* createIf(ASTNode* condition, ASTNode* thenBranch, ASTNode* elseBranch);
ASTNode* createWhile(ASTNode* condition, ASTNode* body);
ASTNode* createRace(ASTNode* left, ASTNode* right);

void printAST(ASTNode* node, int level);

#endif /* AST_H */
