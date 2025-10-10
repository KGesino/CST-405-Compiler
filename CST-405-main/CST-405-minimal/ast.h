#ifndef AST_H
#define AST_H

/* ABSTRACT SYNTAX TREE (AST)
 * The AST is an intermediate representation of the program structure
 * It represents the hierarchical syntax of the source code
 * Each node represents a construct in the language
 */

/* NODE TYPES - Different kinds of AST nodes in our language */
typedef enum {
    NODE_NUM,       /* Numeric literal (e.g., 42) */
    NODE_VAR,       /* Variable reference (e.g., x) */
    NODE_BINOP,     /* Binary operation (e.g., x + y) */
    NODE_DECL,      /* Variable declaration (e.g., int x) */
    NODE_ASSIGN,    /* Assignment statement (e.g., x = 10) */
    NODE_PRINT,     /* Print statement (e.g., print(x)) */
    NODE_STMT_LIST,  /* List of statements (program structure) */
    /* arrays */
    NODE_ARRAY_DECL,     /* Array declaration: int a[SIZE] */
    NODE_ARRAY_ASSIGN,   /* Element assignment: a[index] = value */
    NODE_ARRAY_ACCESS,    /* Element access expression: a[index] */
    /* NEW: 2D Array nodes */
    NODE_ARRAY2D_DECL,     /* 2D array declaration: int a[rows][cols] */
    NODE_ARRAY2D_ASSIGN,   /* 2D array element assignment: a[i][j] = val */
    NODE_ARRAY2D_ACCESS    /* 2D array access: a[i][j] */
} NodeType;

/* AST NODE STRUCTURE
 * Uses a union to efficiently store different node data
 * Only the relevant fields for each node type are used
 */
typedef struct ASTNode {
    NodeType type;  /* Identifies what kind of node this is */
    
    /* Union allows same memory to store different data types */
    union {
        /* Literal number value (NODE_NUM) */
        int num;
        
        /* Variable or declaration name (NODE_VAR, NODE_DECL) */
        char* name;
        /* int value*/ /* for potential future use in declarations*/
        
        
        /* Binary operation structure (NODE_BINOP) */
        struct {
            char op;                    /* Operator character ('+') */
            struct ASTNode* left;       /* Left operand */
            struct ASTNode* right;      /* Right operand */
        } binop;
        
        /* Assignment structure (NODE_ASSIGN) */
        struct {
            char* var;                  /* Variable being assigned to */
            struct ASTNode* value;      /* Expression being assigned */
        } assign;
        
        /* Print expression (NODE_PRINT) */
        struct ASTNode* expr;
        
        /* Statement list structure (NODE_STMT_LIST) */
        struct {
            struct ASTNode* stmt;       /* Current statement */
            struct ASTNode* next;       /* Rest of the list */
        } stmtlist;
        /*  Array declaration node (NODE_ARRAY_DECL) */
        struct {
            char* name;          /* array name */
            int size;            /* array size (assumed known at parse time) */
        } arrdecl;

        /* Array element assignment (NODE_ARRAY_ASSIGN) */
        struct {
            char* var;           /* array name */
            struct ASTNode* index; /* index expression */
            struct ASTNode* value; /* value expression */
        } arrassign;

        /*  Array element access (NODE_ARRAY_ACCESS) */
        struct {
            char* name;            /* array name */
            struct ASTNode* index; /* index expression */
        } arraccess;
        /* ---------- 2D Array ---------- */
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
    } data;
} ASTNode;

/* AST CONSTRUCTION FUNCTIONS
 * These functions are called by the parser to build the tree
 */
ASTNode* createNum(int value);                                   /* Create number node */
ASTNode* createVar(char* name);                                  /* Create variable node */
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right);   /* Create binary op node */
ASTNode* createDecl(char* name);
/* ASTNode* createDeclWithAssgn(char* name, int value);*/                                 /* Create declaration node */
ASTNode* createAssign(char* var, ASTNode* value);               /* Create assignment node */
ASTNode* createPrint(ASTNode* expr);                            /* Create print node */
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2);        /* Create statement list */
/* array constructors */
ASTNode* createArrayDecl(char* name, int size);
ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value);
ASTNode* createArrayAccess(char* name, ASTNode* index);
/* 2D array constructors */
ASTNode* createArray2DDecl(char* name, int rows, int cols);
ASTNode* createArray2DAssign(char* name, ASTNode* row, ASTNode* col, ASTNode* value);
ASTNode* createArray2DAccess(char* name, ASTNode* row, ASTNode* col);
/* AST DISPLAY FUNCTION */
void printAST(ASTNode* node, int level);                        /* Pretty-print the AST */

#endif