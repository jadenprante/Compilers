#pragma once
#include "cDeclNode.h"
#include "cSymbol.h"

class cVarDeclNode : public cDeclNode
{
public:
    cVarDeclNode(cSymbol *type, cSymbol *name) : cDeclNode()
    {
        AddChild(type);
        AddChild(name);
    }

    virtual std::string NodeType() override { return "var_decl"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};
