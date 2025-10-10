%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
%}

%option nounput
%option noinput

%%

int             { return INT; }
print           { return PRINT; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    return ID;
}

[0-9]+ {
    yylval.num = atoi(yytext);
    return NUM;
}

"+"     { return '+'; }
"-"     { return '-'; }
"="     { return '='; }
";"     { return ';'; }
"("     { return '('; }
")"     { return ')'; }
"["     { return '['; }
"]"     { return ']'; }
","     { return ','; }
"{"     { return '{'; }
"}"     { return '}'; }

[ \t\r\n]+      { /* skip whitespace */ }

"//"[^\n]*      { /* skip single-line comments */ }

"/*"([^*]|"*"+[^*/])*"*"+"/"    { /* skip multi-line comments */ }

. {
    printf("Lexical Error: Unknown character '%c'\n", *yytext);
}

%%

int yywrap(void) { return 1; }