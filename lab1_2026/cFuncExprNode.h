#pragma once

#include "cExprNode.h"
#include "cSymbol.h"
#include "cParamListNode.h"
#include "cVisitor.h"

class cFuncExprNode : public cExprNode
{
private:
    cSymbol *m_name;
    cParamListNode *m_params;

public:
    cFuncExprNode(cSymbol *name, cParamListNode *params)
        : m_name(name), m_params(params)
    {
        AddChild(m_name);
        AddChild(m_params);
    }

    virtual string NodeType() override { return "funcexpr"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};
