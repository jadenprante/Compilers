#pragma once
#include "cDeclNode.h"
#include "cDeclsNode.h"
#include "cSymbol.h"

class cStructDeclNode : public cDeclNode
{
public:
    cStructDeclNode(cDeclsNode *fields, cSymbol *name) : cDeclNode()
    {
        AddChild(fields);
        AddChild(name);
    }

    virtual std::string NodeType() override { return "struct_decl"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};