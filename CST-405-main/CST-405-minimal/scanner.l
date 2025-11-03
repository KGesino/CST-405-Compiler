%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

int curr_col = 1;
%}

%option noyywrap
%option nounput
%option noinput
%option yylineno

%x COMMENT

%%


int         { return INT; }
float       { return FLOAT; }
bool        { return BOOL; }
print       { return PRINT; }
return      { return RETURN; }
void        { return VOID; }
if          { return IF; }
else        { return ELSE; }
while       { return WHILE; }


true        { yylval.num = 1; return BOOL_LIT; }
false       { yylval.num = 0; return BOOL_LIT; }


">="        { return GE; }
"<="        { return LE; }
"=="        { return EQ; }
"!="        { return NE; }
">"         { return GT; }
"<"         { return LT; }


"&&"        { return AND; }
"||"        { return OR; }
"!"         { return NOT; }


[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    return ID;
}


[0-9]+\.[0-9]+ {
    yylval.fnum = (float)atof(yytext);
    return FLOAT_LIT;
}

[0-9]+ {
    yylval.num = atoi(yytext);
    return NUM;
}


[+\-=\;()\[\],{}*/]   { return yytext[0]; }


[ \t]+      { curr_col += yyleng; }
\n          { curr_col = 1; }
\r          { /* ignore Windows carriage return */ }



"//".*      { }


"/*"        { BEGIN(COMMENT); }
<COMMENT>[^*\n]+   { }
<COMMENT>"*"+[^*/] { }
<COMMENT>\n        { curr_col = 1; }
<COMMENT>"*"+"/"   { BEGIN(INITIAL); }
<COMMENT>\r        { /* ignore CR inside comments */ }



. {
    fprintf(stderr,
        "Lexical Error: Unknown character '%c' at line %d, column %d\n",
        *yytext, yylineno, curr_col);
    curr_col += yyleng;
}

%%
