%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* externs from scanner / main */
extern int yylex();
extern FILE* yyin;
extern char* yytext;

/* Optional: define this in main.c as:
   const char* g_input_filename = NULL;
   and set it before yyparse(): g_input_filename = argv[1]; */
extern const char* g_input_filename;

void yyerror(const char* msg);

ASTNode* root = NULL;   /* Root of the Abstract Syntax Tree */
%}

/* ============================================================
 * BISON SETTINGS
 * ============================================================ */
%define parse.error detailed
%locations
%start program

/* ============================================================
 * SEMANTIC VALUE TYPES
 * ============================================================ */
%union {
    int num;
    float fnum;        /* float literals */
    char* str;
    struct ASTNode* node;
}

/* ============================================================
 * TOKENS
 * ============================================================ */
%token <num> NUM
%token <fnum> FLOAT_LIT
%token <str> ID
%token INT FLOAT PRINT RETURN VOID IF ELSE WHILE
%token GT LT GE LE EQ NE                /* relational operators */

/* ============================================================
 * NONTERMINALS
 * ============================================================ */
%type <node> program func_list func_decl param_list param stmt_list stmt decl assign expr print_stmt return_stmt
%type <node> arg_list id_list
%type <node> arr_decl arr_assign arr2d_decl arr2d_assign
%type <node> if_stmt
%type <str> type

/* ============================================================
 * OPERATOR PRECEDENCE
 * ============================================================ */
%left '+' '-'
%left '*' '/'
%left GT LT GE LE EQ NE
%nonassoc IFX
%nonassoc ELSE

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
    INT   { $$ = "int"; }
  | FLOAT { $$ = "float"; }
  | VOID  { $$ = "void"; }
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
  | if_stmt
  | '{' stmt_list '}'        { $$ = $2; }    /* compound block */
  | '{' '}'                  { $$ = NULL; }  /* empty block */
  ;

/* =========================
   IF STATEMENT
   ========================= */
if_stmt:
    IF '(' expr ')' stmt %prec IFX
        { $$ = createIf($3, $5, NULL); }
  | IF '(' expr ')' stmt ELSE stmt
        { $$ = createIf($3, $5, $7); }
  ;

/* =========================
   DECLARATIONS
   ========================= */
id_list:
    ID                      { $$ = createDecl($1); free($1); }
  | id_list ',' ID          { $$ = createDeclList($1, createDecl($3)); free($3); }
  ;

decl:
    type id_list ';'        { $$ = $2; }
  ;

/* 1D Array Declaration */
arr_decl:
    type ID '[' NUM ']' ';'  { $$ = createArrayDecl($2, $4); free($2); }
  ;

/* 2D Array Declaration */
arr2d_decl:
    type ID '[' NUM ']' '[' NUM ']' ';' {
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
    /* atoms */
    NUM                           { $$ = createNum($1); }
  | FLOAT_LIT                     { $$ = createFloatNode($1); }
  | ID                            { $$ = createVar($1); free($1); }
  | '(' expr ')'                  { $$ = $2; }

    /* array accesses */
  | ID '[' expr ']'               { $$ = createArrayAccess($1, $3); free($1); }
  | ID '[' expr ']' '[' expr ']'  { $$ = createArray2DAccess($1, $3, $6); free($1); }

    /* arithmetic */
  | expr '+' expr                 { $$ = createBinOp('+', $1, $3); }
  | expr '-' expr                 { $$ = createBinOp('-', $1, $3); }
  | expr '*' expr                 { $$ = createBinOp('*', $1, $3); }
  | expr '/' expr                 { $$ = createBinOp('/', $1, $3); }

    /* relational */
  | expr GT expr                  { $$ = createBinOp('>', $1, $3); }
  | expr LT expr                  { $$ = createBinOp('<', $1, $3); }
  | expr GE expr                  { $$ = createBinOp('G', $1, $3); } /* G for >= */
  | expr LE expr                  { $$ = createBinOp('L', $1, $3); } /* L for <= */
  | expr EQ expr                  { $$ = createBinOp('E', $1, $3); } /* E for == */
  | expr NE expr                  { $$ = createBinOp('N', $1, $3); } /* N for != */

    /* function calls */
  | ID '(' arg_list ')'           { $$ = createFuncCall($1, $3); free($1); }
  | ID '(' ')'                    { $$ = createFuncCall($1, NULL); free($1); }
  ;

arg_list:
    expr                          { $$ = $1; }
  | arg_list ',' expr             { $$ = createArgList($1, $3); }
  ;

/* =========================
   PRINT STATEMENT
   ========================= */
print_stmt:
    PRINT '(' expr ')' ';'        { $$ = createPrint($3); }
  ;

%%

/* =========================
   ERROR HANDLING
   ========================= */
void yyerror(const char* msg) {
    extern YYLTYPE yylloc;
    extern char* yytext;

    int line_no = yylloc.first_line > 0 ? yylloc.first_line : 1;
    int col_no  = yylloc.first_column > 0 ? yylloc.first_column : 1;

    if (g_input_filename) {
        FILE* src = fopen(g_input_filename, "r");
        if (src) {
            char linebuf[1024];
            int current = 1;
            while (fgets(linebuf, sizeof(linebuf), src)) {
                if (current == line_no) {
                    size_t L = strlen(linebuf);
                    while (L > 0 && (linebuf[L-1] == '\n' || linebuf[L-1] == '\r'))
                        linebuf[--L] = '\0';

                    fprintf(stderr,
                        "✗ Syntax Error: %s\n"
                        "  → Line %d, column %d\n"
                        "  → Near token: '%s'\n\n"
                        "    %s\n"
                        "    %*s^\n",
                        msg, line_no, col_no,
                        yytext ? yytext : "(unknown)",
                        linebuf, col_no, "");
                    fclose(src);
                    return;
                }
                current++;
            }
            fclose(src);
        }
    }

    fprintf(stderr,
        "✗ Syntax Error: %s at line %d, column %d (near '%s')\n",
        msg, line_no, col_no, yytext ? yytext : "(unknown)");
}
