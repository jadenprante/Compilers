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
        AddChild(op);      // now compiler knows cOpNode inherits cAstNode
        AddChild(right);
    }
	virtual string AttributesToString() override
    {
        return " op=\"" + m_op + "\"";
    }


    virtual string NodeType() override { return "expr"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
private:
    string m_op;
};
