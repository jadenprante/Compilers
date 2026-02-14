//**************************************
// cExprNode.h
//
// Defines base class for all expressions
//
// This is a pure virtual class because there is no definition for
// cAstNode::ToString()
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#pragma once
#include "cStmtNode.h"

class cExprNode : public cStmtNode
{
public:
    cExprNode() : cStmtNode() {}

    // Convenience constructor for binary expressions
    cExprNode(cExprNode *lhs, cAstNode *op, cExprNode *rhs) : cStmtNode()
    {
        AddChild(lhs);
        AddChild(op);
        AddChild(rhs);
    }

    virtual string NodeType() override { return string("expr"); }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};