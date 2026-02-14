#pragma once
#include "cStmtNode.h"
#include "cExprNode.h"

class cWhileNode : public cStmtNode
{
public:
    cWhileNode(cExprNode *expr, cStmtNode *stmt)
    {
        AddChild(expr);
        AddChild(stmt);
    }

    virtual std::string NodeType() override { return "while"; }
    virtual void Visit(cVisitor *visitor) override
    {
        visitor->Visit(this);
    }

};
