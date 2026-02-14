%option noyywrap

%{
#include <cstdlib>
#include <cstring>
#include "langparse.h"
#include "cSymbol.h"
#include "cSymbolTable.h"

extern cSymbolTable g_symbolTable;
%}

%%

"if"        { return IF; }
"else"      { return ELSE; }
"endif"     { return ENDIF; }
"prints"    { return PRINT; }
"return"    { return RETURN; }
"struct"    { return STRUCT; }
"array"     { return ARRAY; }
"local"     { return LOCAL; }
"global"    { return GLOBAL; }
"lookup"    { return LOOKUP; }
"insert"    { return INSERT; }

"char"      { yylval.symbol = g_symbolTable.Find("char"); return CHAR; }
"int"       { yylval.symbol = g_symbolTable.Find("int"); return INT; }
"long"      { yylval.symbol = g_symbolTable.Find("long"); return LONG; }
"float"     { yylval.symbol = g_symbolTable.Find("float"); return FLOAT; }
"double"    { yylval.symbol = g_symbolTable.Find("double"); return DOUBLE; }


[0-9]+\.[0-9]+ {
    yylval.float_val = atof(yytext);
    return FLOAT_VAL;
}

[0-9]+ {
    yylval.int_val = atoi(yytext);
    return INT_VAL;
}

\"([^\\\"]|\\.)*\" {
    yylval.str_val = strdup(yytext+1);
    yylval.str_val[strlen(yylval.str_val)-1] = 0;
    return STRING_LIT;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    cSymbol *sym = g_symbolTable.Find(yytext);
    if (!sym)
        sym = new cSymbol(yytext);
    yylval.symbol = sym;
    return IDENTIFIER;
}

"=="    { return EQUALS; }
"!="    { return NOT_EQUALS; }
">="    { return GE; }
"<="    { return LE; }
"&&"    { return AND; }
"||"    { return OR; }
"+"     { return '+'; }
"-"     { return '-'; }
"*"     { return '*'; }
"/"     { return '/'; }
"%"     { return '%'; }

"{"     { return OPEN; }
"}"     { return CLOSE; }
"("     { return '('; }
")"     { return ')'; }
";"     { return ';'; }

[ \t\r\n]+   ;

.           { return yytext[0]; }

%%
