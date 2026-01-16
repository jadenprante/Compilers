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
#include "cSymbol.h"
#include "cSymbolTable.h"
#include "lex.h"
#include "tokens.h"

cSymbolTable g_symbolTable;
long long cSymbol::nextId = 0;
yylval_t yylval;
int g_insert = 1;           // insert symbols into the table
int g_local = 0;            // local lookups only

// Process identifiers and insert/find in symbol table
static int ProcessID()
{
    std::string name(yytext);
    cSymbol* sym; 
    if (g_insert)
    {
        sym = g_symbolTable.FindLocal(name);
        if (!sym)
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

int main(int argc, char** argv)
{
    const char* outfile_name;
    int token;

    std::cout << "Jaden Prante" << std::endl;

    // open input file
    if (argc > 1)
    {
        yyin = fopen(argv[1], "r");
        if (!yyin)
        {
            std::cerr << "Unable to open input file: " << argv[1] << "\n";
            exit(-1);
        }
    }

    // redirect output if requested
    if (argc > 2)
    {
        outfile_name = argv[2];
        FILE* output = fopen(outfile_name, "w");
        if (!output)
        {
            std::cerr << "Unable to open output file: " << outfile_name << "\n";
            exit(-1);
        }
        int output_fd = fileno(output);
        if (dup2(output_fd, 1) != 1)
        {
            std::cerr << "Unable to redirect output to " << outfile_name << "\n";
            exit(-2);
        }
    }

    // TEST2 flag
    bool do_test2 = (argc > 3);

    if (!do_test2) { std::cout << "<program>\n"; }

    token = yylex();
    while (token != 0)
    {
        if (do_test2)
        {
            // TEST2 output
            if (token == IDENTIFIER)
                printf("%d:%s:%lld\n", token, yytext, yylval.symbol->GetId());
            else
                printf("%d:%s\n", token, yytext);
        }
        else
        {
            cSymbol* sym = nullptr;

            switch (token)
            {
            case IDENTIFIER:
                sym = yylval.symbol;
                if (!g_insert)
                {
                    if (g_local)
                        sym = g_symbolTable.FindLocal(sym->GetName());
                    else
                        sym = g_symbolTable.Find(sym->GetName());
                    if (!sym) break; // don't print unknown temp symbols
                    yylval.symbol = sym;
                }
                std::cout << "<sym id=\"" << sym->GetId() << "\" name=\"" << sym->GetName() << "\"/>\n";
                break;

            case GLOBAL:
                sym = g_symbolTable.FindLocal("GLOBAL");
                if (!sym)
                {
                    sym = new cSymbol("GLOBAL");
                    g_symbolTable.Insert(sym);
                }
                std::cout << "<sym id=\"" << sym->GetId() << "\" name=\"" << sym->GetName() << "\"/>\n";
                g_local = 0;
                break;

            case INSERT:
                sym = g_symbolTable.FindLocal("INSERT");
                if (!sym)
                {
                    sym = new cSymbol("INSERT");
                    g_symbolTable.Insert(sym);
                }
                std::cout << "<sym id=\"" << sym->GetId() << "\" name=\"" << sym->GetName() << "\"/>\n";
                g_insert = 1;
                break;

            case LOOKUP:
                sym = g_symbolTable.FindLocal("LOOKUP");
                if (!sym)
                {
                    sym = new cSymbol("LOOKUP");
                    g_symbolTable.Insert(sym);
                }
                std::cout << "<sym id=\"" << sym->GetId() << "\" name=\"" << sym->GetName() << "\"/>\n";
                g_insert = 0;
                break;

            case LOCAL:
                sym = g_symbolTable.FindLocal("LOCAL");
                if (!sym)
                {
                    sym = new cSymbol("LOCAL");
                    g_symbolTable.Insert(sym);
                }
                std::cout << "<sym id=\"" << sym->GetId() << "\" name=\"" << sym->GetName() << "\"/>\n";
                g_local = 1;
                break;

            case OPEN:
                std::cout << "<open/>\n";
                g_symbolTable.IncreaseScope();
                break;

            case CLOSE:
                std::cout << "<close/>\n";
                g_symbolTable.DecreaseScope();
                break;
            default:
                break;
            }
        }
        token = yylex();
    }
    if (!do_test2) { std::cout << "</program>\n"; }
    return 0;
}
