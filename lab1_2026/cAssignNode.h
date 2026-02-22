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

    cExprNode* GetLhs();
    cExprNode* GetRhs();

    virtual std::string NodeType() override { return "assign"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
    /*void cSemanticVisitor::Visit(cAssignNode *node)
    {
        VisitAllChildren(node);

        cDeclNode *lhsType = node->GetLhs()->GetType();
        cDeclNode *rhsType = node->GetRhs()->GetType();

        if (!lhsType->IsCompatibleWith(rhsType))
        {
            SemanticParseError("Cannot assign " +
            rhsType->GetName() + " to " +
            lhsType->GetName());
        }
    }*/
};
