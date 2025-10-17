%{
/* ============================================================
 * SYNTAX ANALYZER (PARSER)
 * Phase 2: Verifies grammar and builds the AST
 * ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex();
extern FILE* yyin;
void yyerror(const char* msg);

ASTNode* root = NULL;   /* Root of the Abstract Syntax Tree */
%}

/* ============================================================
 * BISON SETTINGS
 * ============================================================ */
%define parse.error detailed   /* verbose syntax error messages */
%locations                     /* track line/column positions */

/* ============================================================
 * SEMANTIC VALUE TYPES
 * ============================================================ */
%union {
    int num;
    char* str;
    struct ASTNode* node;
}

/* ============================================================
 * TOKENS
 * ============================================================ */
%token <num> NUM
%token <str> ID
%token INT PRINT RETURN VOID
%token IF ELSE WHILE

/* ============================================================
 * NONTERMINALS
 * ============================================================ */
%type <node> program func_list func_decl param_list param stmt_list stmt decl assign expr print_stmt return_stmt
%type <node> arg_list id_list
%type <node> arr_decl arr_assign arr2d_decl arr2d_assign
%type <str> type

/* ============================================================
 * OPERATOR PRECEDENCE
 * ============================================================ */
%left '+' '-'

%%

/* =========================
   PROGRAM STRUCTURE
   ========================= */
program:
    func_list { root = $1; }
    ;

func_list:
    func_decl                { $$ = $1; }
  | func_list func_decl      { $$ = createFuncList($1, $2); }
  ;

/* =========================
   FUNCTION DECLARATIONS
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
   PARAMETERS
   ========================= */
param_list:
    param                    { $$ = $1; }
  | param_list ',' param     { $$ = createParamList($1, $3); }
  ;

param:
    type ID                  { $$ = createParam($1, $2); free($2); }
  ;

/* =========================
   STATEMENT LIST
   ========================= */
stmt_list:
    stmt                     { $$ = $1; }
  | stmt_list stmt           { $$ = createStmtList($1, $2); }
  ;

/* =========================
   STATEMENTS
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
   DECLARATIONS
   ========================= */
id_list:
    ID                      { $$ = createDecl($1); free($1); }
  | id_list ',' ID          { $$ = createDeclList($1, createDecl($3)); free($3); }
  ;

decl:
    INT id_list ';'         { $$ = $2; }
  ;

/* 1D Array Declaration: int a[NUM]; */
arr_decl:
    INT ID '[' NUM ']' ';'  { $$ = createArrayDecl($2, $4); free($2); }
  ;

/* 2D Array Declaration: int a[NUM][NUM]; */
arr2d_decl:
    INT ID '[' NUM ']' '[' NUM ']' ';' {
        $$ = createArray2DDecl($2, $4, $7);
        free($2);
    }
  ;

/* =========================
   ASSIGNMENTS
   ========================= */
assign:
    ID '=' expr ';'         { $$ = createAssign($1, $3); free($1); }
  ;

/* 1D Array Element */
arr_assign:
    ID '[' expr ']' '=' expr ';'
        { $$ = createArrayAssign($1, $3, $6); free($1); }
  ;

/* 2D Array Element */
arr2d_assign:
    ID '[' expr ']' '[' expr ']' '=' expr ';'
        { $$ = createArray2DAssign($1, $3, $6, $9); free($1); }
  ;

/* =========================
   RETURN STATEMENT
   ========================= */
return_stmt:
    RETURN expr ';'         { $$ = createReturn($2); }
  | RETURN ';'              { $$ = createReturn(NULL); }
  ;

/* =========================
   EXPRESSIONS
   ========================= */
expr:
    NUM                     { $$ = createNum($1); }
  | ID                      { $$ = createVar($1); free($1); }
  | ID '[' expr ']'         { $$ = createArrayAccess($1, $3); free($1); }
  | ID '[' expr ']' '[' expr ']' { $$ = createArray2DAccess($1, $3, $6); free($1); }
  | expr '+' expr           { $$ = createBinOp('+', $1, $3); }
  | expr '-' expr           { $$ = createBinOp('-', $1, $3); }
  | ID '(' arg_list ')'     { $$ = createFuncCall($1, $3); free($1); }
  | ID '(' ')'              { $$ = createFuncCall($1, NULL); free($1); }
  ;

arg_list:
    expr                    { $$ = $1; }
  | arg_list ',' expr       { $$ = createArgList($1, $3); }
  ;

/* =========================
   PRINT STATEMENT
   ========================= */
print_stmt:
    PRINT '(' expr ')' ';'  { $$ = createPrint($3); }
  ;

%%

/* =========================
   ERROR HANDLING
   ========================= */
void yyerror(const char* msg) {
    extern YYLTYPE yylloc;
    fprintf(stderr,
        "Syntax Error: %s at line %d, column %d\n",
        msg,
        yylloc.first_line,
        yylloc.first_column);
}
