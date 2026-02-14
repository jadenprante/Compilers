#pragma once
#include "cStmtNode.h"
#include "cExprNode.h"

class cReturnNode : public cStmtNode
{
public:
    explicit cReturnNode(cExprNode *expr = nullptr) : cStmtNode()
    {
        AddChild(expr);
    }

    virtual std::string NodeType() override { return "return"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};
