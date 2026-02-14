#pragma once

#include "cExprNode.h"
#include "cSymbol.h"

class cVarExprNode : public cExprNode
{
public:
    cVarExprNode(cSymbol* sym) : m_symbol(sym)
    {
        AddChild(sym);
    }

    virtual string NodeType() override { return "var"; }
    virtual string AttributesToString() override
    {
        return " name=\"" + m_symbol->GetName() + "\"";
    }
    virtual void Visit(cVisitor* visitor) override { visitor->Visit(this); }

private:
    cSymbol* m_symbol;
};
