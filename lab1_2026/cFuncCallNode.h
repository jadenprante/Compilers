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

    cSymbol* GetSymbol();
    int ArgCount();
    cExprNode* GetArg(int i);

    virtual std::string NodeType() override { return "funcCall"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
    virtual cDeclNode* GetType()
    {
        cSymbol* sym = dynamic_cast<cSymbol*>(GetChild(0));
        return sym->GetDecl()->GetType();
    }
    /*void cSemanticVisitor::Visit(cFuncCallNode *node)
    {
        VisitAllChildren(node);

        cSymbol *sym = node->GetSymbol();
        cDeclNode *decl = sym->GetDecl();

        if (!decl->IsFunc()) return;

         cFuncDeclNode *func = dynamic_cast<cFuncDeclNode*>(decl);

        if (node->ArgCount() != func->ParamCount())
        {
            SemanticParseError(sym->GetName() +
            " called with wrong number of arguments");
            return;
        }

        for (int i = 0; i < node->ArgCount(); i++)
        {
            if (!func->GetParam(i)->GetType()->IsCompatibleWith(
                 node->GetArg(i)->GetType()))
            {
                SemanticParseError("function " +
                sym->GetName() +
                " called with incompatible argument");
            }
        }   

        if (!func->HasDefinition())
        {
            SemanticParseError("Function " +
            sym->GetName() +
            " not fully defined");
        }
    }*/
};
