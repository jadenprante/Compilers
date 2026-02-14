#pragma once
#include "cAstNode.h"
#include "cExprNode.h"

class cParamsNode : public cAstNode
{
public:
    cParamsNode() : cAstNode() {}
    explicit cParamsNode(cExprNode *first) : cAstNode() { AddChild(first); }

    void Insert(cExprNode *expr) { AddChild(expr); }

    virtual std::string NodeType() override { return "params"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};