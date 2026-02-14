#pragma once

#include "cExprNode.h"
#include "cOpNode.h"
#include "cVisitor.h"

class cUnaryExprNode : public cExprNode
{
private:
    cOpNode   *m_op;
    cExprNode *m_expr;

public:
    cUnaryExprNode(cOpNode *op, cExprNode *expr)
        : m_op(op), m_expr(expr)
    {
        AddChild(m_op);
        AddChild(m_expr);
    }

    virtual string NodeType() override { return "unaryexpr"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};
