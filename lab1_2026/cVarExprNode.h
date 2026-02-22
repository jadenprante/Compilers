#pragma once

#include "cExprNode.h"
#include "cSymbol.h"

class cVarExprNode : public cExprNode
{
public:
    cVarExprNode(cSymbol* sym) : m_symbol(sym)
    {
        AddChild(sym);
    }

    cSymbol* GetSymbol();

    virtual string NodeType() override { return "var"; }
    virtual string AttributesToString() override
    {
        return " name=\"" + m_symbol->GetName() + "\"";
    }
    virtual void Visit(cVisitor* visitor) override { visitor->Visit(this); }
    virtual cDeclNode* GetType()
    {
        return m_symbol->GetDecl()->GetType();
    }
    /*void cSemanticVisitor::Visit(cVarExprNode *node)
    {
        VisitAllChildren(node);

        cDeclNode *decl = node->GetSymbol()->GetDecl();

        if (decl->IsFunc())
        {
            SemanticParseError("Symbol " +
            decl->GetName() +
            " is a function, not a variable");
        }
    }*/
private:
    cSymbol* m_symbol;
};
