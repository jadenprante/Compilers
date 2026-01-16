%{
//**************************************
// lang.l
//
// Scanner definition file
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

// Illustration showing how to use {} to control scope
// NOTE: this is pseudo-code illustrating how you can adapt your current lang.l


#include "tokens.h"
#include "lex.h"
#include "cSymbolTable.h"
#include <string>

using namespace std;

extern cSymbolTable g_symbolTable;
extern yylval_t yylval;
extern bool g_insert;

static int ProcessID()
{
    string name(yytext);
    cSymbol *sym;

    if (g_insert)
    {
        sym = g_symbolTable.FindLocal(name);
        if (sym == nullptr)
        {
            sym = new cSymbol(name);
            g_symbolTable.Insert(sym);
        }
    }
    else
    {
        sym = new cSymbol(name);
    }

    yylval.symbol = sym;
    return IDENTIFIER;
}

int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

%}

%%
[ \t\r\n]+                ;
"//".*                    ;

"{"                       { return OPEN; }
"}"                       { return CLOSE; }

"program"                 { return PROGRAM; }
"if"                      { return IF; }
"else"                    { return ELSE; }
"endif"                   { return ENDIF; }
"while"                   { return WHILE; }
"print"                   { return PRINT; }
"prints"                  { return PRINTS; }
"char"                    { return CHAR; }
"int"                     { return INT; }
"long"                    { return LONG; }
"float"                   { return FLOAT; }
"double"                  { return DOUBLE; }
"struct"                  { return STRUCT; }
"array"                   { return ARRAY; }
"return"                  { return RETURN; }

[A-Za-z_][A-Za-z0-9_]*     { return ProcessID(); }

[0-9]+\.[0-9]+            { yylval.symbol = nullptr; return FLOAT_VAL; }
[0-9]+                     { yylval.symbol = nullptr; return INT_VAL; }

\"[^\"]*\"                { yylval.symbol = nullptr; return STRING_LIT; }

"=="                      { return EQUALS; }
"!="                      { return NOT_EQUALS; }
">="                      { return GE; }
"<="                      { return LE; }
"&&"                      { return AND; }
"||"                      { return OR; }

"("                       { return '('; }
")"                       { return ')'; }
";"                       { return ';'; }
","                       { return ','; }
"."                       { return '.'; }
"+"                       { return '+'; }
"-"                       { return '-'; }
"*"                       { return '*'; }
"/"                       { return '/'; }
"%"                       { return '%'; }
"="                       { return '='; }
">"                       { return '>'; }
"<"                       { return '<'; }
"["                       { return '['; }
"]"                       { return ']'; }

.                         { return JUNK_TOKEN; }
%%

int yywrap() { return 1; }
