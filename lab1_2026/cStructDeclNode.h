#pragma once
#include "cDeclNode.h"
#include "cDeclsNode.h"
#include "cSymbol.h"
#include "cSymbolTable.h"

extern cSymbolTable g_symbolTable;
void SemanticParseError(std::string error);

class cStructDeclNode : public cDeclNode
{
public:
    cStructDeclNode(cDeclsNode *fields, cSymbol *name)
    {
        /*if (g_symbolTable.FindLocal(name->GetName()) != nullptr)
        {
            SemanticParseError("Symbol " + name->GetName() +
                               " already defined in current scope");
            return;
        }*/

        g_symbolTable.Insert(name);
        name->SetDecl(this);

        AddChild(fields);
        AddChild(name);
    }

    virtual std::string NodeType() override { return "struct_decl"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }

    virtual bool IsStruct() { return true; }
    virtual bool IsType() { return true; }

    virtual cDeclNode* GetType() { return this; }
    cSymbol* GetSymbol()
    {
        return dynamic_cast<cSymbol*>(GetChild(1));
    }
    virtual std::string GetName() override
    {
        return GetSymbol()->GetName();
    }
};
