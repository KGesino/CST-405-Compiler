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

%%

int         { return INT; }
print       { return PRINT; }
return      { return RETURN; }
void        { return VOID; }
if          { return IF; }
else        { return ELSE; }
while       { return WHILE; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    return ID;
}

[0-9]+ {
    yylval.num = atoi(yytext);
    return NUM;
}

[+\-=\;()\[\],{}]   { return yytext[0]; }

[ \t]+      { curr_col += yyleng; }
\n          { curr_col = 1; }

"//".*      { /* skip comment */ }
"/*"([^*]|\*+[^*/])*\*+"/"   { /* skip comment */ }

. {
    fprintf(stderr, "Lexical Error: Unknown character '%c' at line %d, column %d\n",
            *yytext, yylineno, curr_col);
    curr_col += yyleng;
}

%%
