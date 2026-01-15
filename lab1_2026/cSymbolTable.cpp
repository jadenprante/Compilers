#include "cSymbolTable.h"
#include "cSymbol.h"
#include <unordered_map>
#include <vector>
#include <string>

using std::string;
using std::unordered_map;
using std::vector;

// One scope = map from name to symbol pointer
using Scope = unordered_map<string, cSymbol*>;

// Stack of scopes (inner-most scope is back())
static vector<Scope> scopes;

// ----------------------------------------
// Constructor
cSymbolTable::cSymbolTable()
{
    // Start with global scope
    IncreaseScope();
}

// ----------------------------------------
// Increase scope
symbolTable_t *cSymbolTable::IncreaseScope()
{
    scopes.push_back(Scope());
    return reinterpret_cast<symbolTable_t*>(&scopes.back());
}

// ----------------------------------------
// Decrease scope
symbolTable_t *cSymbolTable::DecreaseScope()
{
    if (!scopes.empty())
        scopes.pop_back();

    if (scopes.empty())
        return nullptr;

    return reinterpret_cast<symbolTable_t*>(&scopes.back());
}

// ----------------------------------------
// Insert symbol into current scope
void cSymbolTable::Insert(cSymbol *sym)
{
    if (scopes.empty())
        IncreaseScope();

    scopes.back()[sym->GetName()] = sym;
}

// ----------------------------------------
// Find symbol (inner → outer)
cSymbol *cSymbolTable::Find(string name)
{
    for (int i = scopes.size() - 1; i >= 0; --i)
    {
        auto it = scopes[i].find(name);
        if (it != scopes[i].end())
            return it->second;
    }
    return nullptr;
}

// ----------------------------------------
// Find symbol in local scope only
cSymbol *cSymbolTable::FindLocal(string name)
{
    if (scopes.empty())
        return nullptr;

    auto it = scopes.back().find(name);
    if (it != scopes.back().end())
        return it->second;

    return nullptr;
}

