#pragma once
#include "cStmtNode.h"
#include "cExprNode.h"
#include "cStmtsNode.h"

class cIfNode : public cStmtNode
{
public:
    cIfNode(cExprNode *cond, cStmtsNode *thenPart, cStmtsNode *elsePart = nullptr)
        : cStmtNode()
    {
        AddChild(cond);
        AddChild(thenPart);
        AddChild(elsePart);
    }

    virtual std::string NodeType() override { return "if"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};