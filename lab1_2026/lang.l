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

#include "cSymbol.h"
#include "cSymbolTable.h"
#include "lex.h"
#include "tokens.h"

//#define DEBUG_OUTPUT
#ifdef DEBUG_OUTPUT
    #define DO_RETURN(a) { return Return(a); }
#else
    #define DO_RETURN(a) { return (a); }
#endif

static int ProcessID();
int Return(int val);
%}

%option noyywrap
%option noinput
%option nounput
%option yylineno

    /* definitions go here. period is an example. */
    /* NOTE: You do not need to use definitions */
letters          [a-z]
%%

    // token definitions. I gave "program" as an example
program                   DO_RETURN(PROGRAM);

%%

    /* definitions go here. whitespace is an example. */
whitespace      '[\t\n\r ]'

%%
{whitespace}+               {} /* Ignore whitespace */
;                           {} /* Ignore semicolons */
    /* control scope with curly braces
     NOTE: This functionality will eventually move to the parser
    */
"{"                         return OPEN;
"}"                         return CLOSE;
LOCAL                       return LOCAL;
GLOBAL                      return GLOBAL;
LOOKUP                      return LOOKUP;
INSERT                      return INSERT;
"if"                        return IF;
"else"                      return ELSE;
"while"                     return WHILE;
[A-Za-z_][A-Za-z0-9_]*   DO_RETURN(Process_ID(yytext));
[0-9]+                      return INT;
[0-9]+"."[0-9]+             return FLOAT;
\"[^\"]*\"                  return STRING_LIT;
[a-z]+                      {
                                return ProcessID();
                            }

%%

//******************************************************
// ProcessID: create symbols in symbol table
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

// This function allows us to do extra processing on each token
// It is used to generate lexer debug info
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}
