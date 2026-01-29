//**************************************
// main.cpp
//
// Main routine for lang compiler.
// This version only runs the lexer
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include "lex.h"
#include "tokens.h"

// ---------- Lab 1 & 2 ----------
#include "cSymbol.h"
#include "cSymbolTable.h"

// ---------- Lab 3 ----------
#include "astnodes.h"
#include "langparse.h"

// --------------------------------------------------
// Globals required by scanner / parser
cSymbolTable g_symbolTable;
long long cSymbol::nextId = 0;
yylval_t yylval;

int g_insert = 1;   // insert symbols
int g_local = 0;   // local vs global lookup

// --------------------------------------------------
int main(int argc, char** argv)
{
    const char* outfile_name;
    int result = 0;

    std::cout << "Jaden Prante" << std::endl;

    // ---------- Open input ----------
    if (argc > 1)
    {
        yyin = fopen(argv[1], "r");
        if (yyin == nullptr)
        {
            std::cerr << "Unable to open file " << argv[1] << "\n";
            exit(-1);
        }
    }

    // ---------- Open output ----------
    if (argc > 2)
    {
        outfile_name = argv[2];
        FILE* output = fopen(outfile_name, "w");
        if (output == nullptr)
        {
            std::cerr << "Unable to open output file " << outfile_name << "\n";
            exit(-1);
        }

        int output_fd = fileno(output);
        if (dup2(output_fd, 1) != 1)
        {
            std::cerr << "Unable to redirect output\n";
            exit(-1);
        }
    }

    // =========================================================
    // LAB 3 MODE — Parser + AST
    // =========================================================
    if (yyparse)
    {
        result = yyparse();

        if (yyast_root != nullptr)
        {
            if (result == 0)
            {
                std::cout << yyast_root->ToString();
            }
            else
            {
                std::cout << " Errors in compile\n";
            }
        }

        if (result == 0 && yylex() != 0)
        {
            std::cout << "Junk at end of program\n";
        }

        return result;
    }

    // =========================================================
    // LAB 1 & 2 MODE — Scanner + Symbol Table
    // =========================================================
    std::cout << "<program>\n";

    int token = yylex();
    while (token != 0)
    {
        if (token == IDENTIFIER)
        {
            cSymbol* sym;
            if (!g_insert)
            {
                if (g_local)
                    sym = g_symbolTable.FindLocal(yylval.symbol->GetName());
                else
                    sym = g_symbolTable.Find(yylval.symbol->GetName());

                if (sym != nullptr)
                    yylval.symbol = sym;
            }

            std::cout << yylval.symbol->ToString() << "\n";
        }
        else if (token == LOCAL)
        {
            std::cout << "<local />\n";
            g_local = 1;
        }
        else if (token == GLOBAL)
        {
            std::cout << "<global />\n";
            g_local = 0;
        }
        else if (token == LOOKUP)
        {
            std::cout << "<lookup />\n";
            g_insert = 0;
        }
        else if (token == INSERT)
        {
            std::cout << "<insert />\n";
            g_insert = 1;
        }
        else if (token == OPEN)
        {
            std::cout << "<open />\n";
            g_symbolTable.IncreaseScope();
        }
        else if (token == CLOSE)
        {
            std::cout << "<close />\n";
            g_symbolTable.DecreaseScope();
        }

        token = yylex();
    }

    std::cout << "</program>\n";
    return result;
}
