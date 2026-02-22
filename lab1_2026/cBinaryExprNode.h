#pragma once

#include "cExprNode.h"
#include "cOpNode.h"

class cBinaryExprNode : public cExprNode
{
public:
    cBinaryExprNode(cExprNode *left, cOpNode *op, cExprNode *right)
        : cExprNode()
    {
        AddChild(left);
        AddChild(op);
        AddChild(right);
    }

    // Required for Lab 5B
    virtual cDeclNode* GetType() override;

    // Helpers
    cExprNode* GetLeft()
    {
        return dynamic_cast<cExprNode*>(GetChild(0));
    }

    cOpNode* GetOpNode()
    {
        return dynamic_cast<cOpNode*>(GetChild(1));
    }

    cExprNode* GetRight()
    {
        return dynamic_cast<cExprNode*>(GetChild(2));
    }

    virtual string NodeType() override { return "binary"; }

    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};
