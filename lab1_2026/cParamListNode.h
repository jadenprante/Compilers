#pragma once

#include "cAstNode.h"
#include "cExprNode.h"
#include "cVisitor.h"
#include <vector>

class cParamListNode : public cAstNode
{
private:
    std::vector<cExprNode*> m_params;

public:
    void Add(cExprNode *expr)
    {
        m_params.push_back(expr);
        AddChild(expr); // for visitor traversal
    }

    virtual string NodeType() override { return "paramlist"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};
