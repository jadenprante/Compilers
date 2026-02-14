#pragma once
#include "cExprNode.h"
#include "cSymbol.h"

class cVarRefNode : public cExprNode
{
public:
    explicit cVarRefNode(cSymbol *base) : cExprNode()
    {
        AddChild(base);
    }

    void AddPart(cAstNode *part) { AddChild(part); }

    virtual std::string NodeType() override { return "varref"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};