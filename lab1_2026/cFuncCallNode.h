#pragma once
#include "cExprNode.h"
#include "cSymbol.h"
#include "cParamsNode.h"

class cFuncCallNode : public cExprNode
{
public:
    explicit cFuncCallNode(cSymbol *name, cParamsNode *params = nullptr)
        : cExprNode()
    {
        AddChild(name);
        AddChild(params);
    }

    virtual std::string NodeType() override { return "funcCall"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
    virtual cDeclNode* GetType()
    {
        cSymbol* sym = dynamic_cast<cSymbol*>(GetChild(0));
        return sym->GetDecl()->GetType();
    }
};
