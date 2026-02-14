#pragma once
#include "cExprNode.h"
#include "cSymbol.h"

class cMemberExprNode : public cExprNode
{
public:
    cMemberExprNode(cExprNode *base, cSymbol *member)
    {
        AddChild(base);
        AddChild(member);
    }

    cExprNode* GetBase() { return dynamic_cast<cExprNode*>(GetChild(0)); }
    cSymbol* GetMember() { return dynamic_cast<cSymbol*>(GetChild(1)); }

    virtual std::string NodeType() override
    {
        return "member";
    }

    virtual void Visit(cVisitor *visitor) override
    {
        visitor->Visit(this);
    }
};
