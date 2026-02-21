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
#include "cDeclNode.h"

class cExprNode : public cStmtNode
{
public:
    cExprNode() : cStmtNode() {}

    virtual string NodeType() override { return "expr"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }

    virtual cDeclNode* GetType() = 0;
};