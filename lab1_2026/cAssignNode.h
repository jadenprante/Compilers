#pragma once
#include "cStmtNode.h"
#include "cVarRefNode.h"
#include "cExprNode.h"

class cAssignNode : public cStmtNode
{
public:
    cAssignNode(cVarRefNode *lhs, cExprNode *rhs) : cStmtNode()
    {
        AddChild(lhs);
        AddChild(rhs);
    }

    virtual std::string NodeType() override { return "assign"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};