#pragma once
#include "cDeclNode.h"
#include "cSymbol.h"
#include "cSymbolTable.h"

extern cSymbolTable g_symbolTable;
void SemanticParseError(std::string error);

class cVarDeclNode : public cDeclNode
{
public:
    cVarDeclNode(cSymbol *type, cSymbol *name)
    {
        /*if (g_symbolTable.FindLocal(name->GetName()) != nullptr)
        {
            SemanticParseError("Symbol " + name->GetName() +
                               " already defined in current scope");
            return;
        }

        g_symbolTable.Insert(name);
        name->SetDecl(this);*/

        AddChild(type);
        AddChild(name);
    }

    virtual std::string NodeType() override { return "var_decl"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }

    virtual bool IsVar() { return true; }

    virtual cDeclNode* GetType()
    {
        return dynamic_cast<cSymbol*>(GetChild(0))->GetDecl();
    }
    virtual std::string GetName() override
    {
        cSymbol *sym = dynamic_cast<cSymbol*>(GetChild(1));
        return sym->GetName();
    }
};
