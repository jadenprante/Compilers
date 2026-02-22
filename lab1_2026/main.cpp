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
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include "lex.h"
#include "tokens.h"

// AST and symbol table
#include "astnodes.h"
#include "langparse.h"
#include "cSymbolTable.h"
#include "cSymbol.h"

// ------------------------------
// Globals
// ------------------------------
cSymbolTable g_symbolTable;        // single definition
long long cSymbol::nextId = 0;     // static member initialization
cAstNode* yyast_root = nullptr;    // AST root

// ------------------------------
// Main
// ------------------------------
int main(int argc, char** argv)
{
    const char* infile = nullptr;
    const char* outfile = nullptr;

    if (argc > 1)
        infile = argv[1];
    if (argc > 2)
        outfile = argv[2];

    // Open input file
    if (infile)
    {
        yyin = fopen(infile, "r");
        if (!yyin)
        {
            std::cerr << "Unable to open input file: " << infile << "\n";
            return -1;
        }
    }

    // Redirect output if file specified
    if (outfile)
    {
        FILE* out = fopen(outfile, "w");
        if (!out)
        {
            std::cerr << "Unable to open output file: " << outfile << "\n";
            return -1;
        }

        int out_fd = fileno(out);
        if (dup2(out_fd, 1) != 1)
        {
            std::cerr << "Unable to redirect stdout\n";
            return -1;
        }
    }

    // ------------------------------
    // Parse program
    // ------------------------------
    int parse_result = yyparse();

    if (yyast_root)
    {
        if (parse_result == 0)
        {
            // Print XML representation of the AST
            std::cout << yyast_root->ToString();
        }
        else
        {
            std::cerr << "Errors in compilation.\n";
        }
    }

    return parse_result;
}
