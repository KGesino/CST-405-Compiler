%{
/* SYNTAX ANALYZER (PARSER)
 * Phase 2 of compilation: checks grammar rules and builds the AST
 * The parser uses tokens from the scanner to verify syntax correctness
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* External declarations for lexer interface */
extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
ASTNode* root = NULL;   /* Root of the Abstract Syntax Tree */
%}

/* SEMANTIC VALUES UNION */
%union {
    int num;                /* For integer literals */
    char* str;              /* For identifiers and type strings */
    struct ASTNode* node;   /* For AST nodes */
}

/* TOKEN DECLARATIONS */
%token <num> NUM
%token <str> ID
%token INT PRINT RETURN VOID
%token IF ELSE WHILE

/* NON-TERMINAL TYPES */
%type <node> program func_list func_decl param_list param stmt_list stmt decl assign expr print_stmt return_stmt
%type <node> arg_list
%type <node> arr_decl arr_assign arr2d_decl arr2d_assign
%type <str> type

/* OPERATOR PRECEDENCE */
%left '+' '-'

%%

/* =========================
   PROGRAM STRUCTURE
   ========================= */
program:
    func_list { root = $1; }
    ;

func_list:
    func_decl { $$ = $1; }
    | func_list func_decl { $$ = createFuncList($1, $2); }
    ;

/* =========================
   FUNCTION DECLARATION RULES
   ========================= */
func_decl:
    type ID '(' param_list ')' '{' stmt_list '}' {
        $$ = createFuncDecl($1, $2, $4, $7);
        free($2);
    }
    | type ID '(' ')' '{' stmt_list '}' {
        $$ = createFuncDecl($1, $2, NULL, $6);
        free($2);
    }
    ;

type:
    INT  { $$ = "int"; }
    | VOID { $$ = "void"; }
    ;

/* =========================
   PARAMETER LIST RULES
   ========================= */
param_list:
    param { $$ = $1; }
    | param_list ',' param { $$ = createParamList($1, $3); }
    ;

param:
    type ID { $$ = createParam($1, $2); free($2); }
    ;

/* =========================
   STATEMENT LIST
   ========================= */
stmt_list:
    stmt { $$ = $1; }
    | stmt_list stmt { $$ = createStmtList($1, $2); }
    ;

/* =========================
   STATEMENT TYPES
   ========================= */
stmt:
    decl
    | assign
    | print_stmt
    | arr_decl
    | arr_assign
    | arr2d_decl
    | arr2d_assign
    | return_stmt
    ;

/* =========================
   DECLARATION RULES
   ========================= */
decl:
    INT ID ';' { $$ = createDecl($2); free($2); }
    ;

/* 1D Array Declaration: int a[NUM]; */
arr_decl:
    INT ID '[' NUM ']' ';' { $$ = createArrayDecl($2, $4); free($2); }
    ;

/* 2D Array Declaration: int a[NUM][NUM]; */
arr2d_decl:
    INT ID '[' NUM ']' '[' NUM ']' ';' {
        $$ = createArray2DDecl($2, $4, $7);
        free($2);
    }
    ;

/* =========================
   ASSIGNMENT RULES
   ========================= */
assign:
    ID '=' expr ';' { $$ = createAssign($1, $3); free($1); }
    ;

/* Array element assignment: a[i] = expr; */
arr_assign:
    ID '[' expr ']' '=' expr ';' { $$ = createArrayAssign($1, $3, $6); free($1); }
    ;

/* 2D Array element assignment: a[i][j] = expr; */
arr2d_assign:
    ID '[' expr ']' '[' expr ']' '=' expr ';' {
        $$ = createArray2DAssign($1, $3, $6, $9);
        free($1);
    }
    ;

/* =========================
   RETURN STATEMENT
   ========================= */
return_stmt:
    RETURN expr ';' { $$ = createReturn($2); }
    | RETURN ';' { $$ = createReturn(NULL); }
    ;

/* =========================
   EXPRESSIONS
   ========================= */
expr:
    NUM { $$ = createNum($1); }
    | ID { $$ = createVar($1); free($1); }
    | ID '[' expr ']' { $$ = createArrayAccess($1, $3); free($1); }
    | ID '[' expr ']' '[' expr ']' {
        $$ = createArray2DAccess($1, $3, $6); free($1);
    }
    | expr '+' expr { $$ = createBinOp('+', $1, $3); }
    | expr '-' expr { $$ = createBinOp('-', $1, $3); }
    /* Function calls in expressions */
    | ID '(' arg_list ')' { $$ = createFuncCall($1, $3); free($1); }
    | ID '(' ')' { $$ = createFuncCall($1, NULL); free($1); }
    ;

/* Function call argument list */
arg_list:
    expr { $$ = $1; }
    | arg_list ',' expr { $$ = createArgList($1, $3); }
    ;

/* =========================
   PRINT STATEMENT
   ========================= */
print_stmt:
    PRINT '(' expr ')' ';' { $$ = createPrint($3); }
    ;

%%

/* =========================
   ERROR HANDLING
   ========================= */
void yyerror(const char* s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}
