%{
#include "lex.h"
#include "tokens.h"
#include <cstdio>
#include <cstdlib>

extern int yylineno;
%}

%%

"end"       { return END; }

[0-9]+      { return NUM; }
[a-zA-Z][a-zA-Z0-9]* { return IDENTIFIER; }

"="         { return ASSIGN; }

"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return TIMES; }
"/"         { return DIV; }

"("         { return '('; }
")"         { return ')'; }
";"         { return SEMI; }

[ \t\r\n]+  ;
"//".*      ;
#.*         ;

.           { return INVALID; }

%%

int yywrap() { return 1; }
