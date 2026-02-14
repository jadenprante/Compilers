//****************************************************
// Starter code for a symbol table definition.
// You are not required to use any of these names, but you will need the 
// described functionality
//

// NOTE: The following typedef will have to be replaced by something meaningful
#pragma once
#include <string>
#include "cSymbol.h"

class cSymbolTable
{
public:
    cSymbolTable();

    // Increase/decrease scope
    void IncreaseScope();
    void DecreaseScope();

    // Insert a symbol
    void Insert(cSymbol *sym);

    // Lookup symbols
    cSymbol *Find(const std::string &name);
    cSymbol *FindLocal(const std::string &name);
};

// Global symbol table
extern cSymbolTable g_symbolTable;

