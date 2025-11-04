%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

int curr_col = 1;
#define DEBUG_LEXER 1
#ifdef DEBUG_LEXER
#  define DBG(fmt, ...) fprintf(stderr, "LEX: " fmt "\n", ##__VA_ARGS__)
#else
#  define DBG(fmt, ...)
#endif
%}

%option noyywrap
%option nounput
%option noinput
%option yylineno

%x COMMENT

%%

int         { DBG("%-10s -> INT", yytext);    return INT; }
float       { DBG("%-10s -> FLOAT", yytext);  return FLOAT; }
bool        { DBG("%-10s -> BOOL", yytext);   return BOOL; }
print       { DBG("%-10s -> PRINT", yytext);  return PRINT; }
return      { DBG("%-10s -> RETURN", yytext); return RETURN; }
void        { DBG("%-10s -> VOID", yytext);   return VOID; }
if          { DBG("%-10s -> IF", yytext);     return IF; }
else        { DBG("%-10s -> ELSE", yytext);   return ELSE; }
while       { DBG("%-10s -> WHILE", yytext);  return WHILE; }

true        { DBG("%-10s -> BOOL_LIT", yytext);  yylval.num = 1; return BOOL_LIT; }
false       { DBG("%-10s -> BOOL_LIT", yytext);  yylval.num = 0; return BOOL_LIT; }

">="        { DBG("%-10s -> GE", yytext); return GE; }
"<="        { DBG("%-10s -> LE", yytext); return LE; }
"=="        { DBG("%-10s -> EQ", yytext); return EQ; }
"!="        { DBG("%-10s -> NE", yytext); return NE; }
">"         { DBG("%-10s -> GT", yytext); return GT; }
"<"         { DBG("%-10s -> LT", yytext); return LT; }

"&&"        { DBG("%-10s -> AND", yytext); return AND; }
"||"        { DBG("%-10s -> OR", yytext);  return OR; }
"!"         { DBG("%-10s -> NOT", yytext); return NOT; }

"*"         { DBG("%-10s -> MUL", yytext); return MUL; }

[a-zA-Z_][a-zA-Z0-9_]* {
    DBG("%-10s -> ID", yytext);
    yylval.str = strdup(yytext);
    return ID;
}

[0-9]+\.[0-9]+([eE][-+]?[0-9]+)? {
    DBG("%-10s -> FLOAT_LIT", yytext);
    yylval.fnum = (float)atof(yytext);
    return FLOAT_LIT;
}

[0-9]+ {
    DBG("%-10s -> NUM", yytext);
    yylval.num = atoi(yytext);
    return NUM;
}

[+\-/=\;()\[\],{}] {
    DBG("%-10s -> '%c'", yytext, yytext[0]);
    return yytext[0];
}

[ \t]+      { curr_col += yyleng; }
\n          { curr_col = 1; }
\r          { }

"//".*      { DBG("%-10s -> comment", yytext); }

"/*"        { BEGIN(COMMENT); }
<COMMENT>[^*\n]+   { }
<COMMENT>"*"+[^*/] { }
<COMMENT>\n        { curr_col = 1; }
<COMMENT>"*"+"/"   { BEGIN(INITIAL); }
<COMMENT>\r        { }

. {
    fprintf(stderr,
        "Lexical Error: Unknown character '%c' at line %d, column %d\n",
        *yytext, yylineno, curr_col);
    curr_col += yyleng;
}

%%
