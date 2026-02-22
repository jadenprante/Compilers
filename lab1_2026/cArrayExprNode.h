#pragma once
#include "cExprNode.h"
#include "cSymbolTable.h"
extern cSymbolTable g_symbolTable;

class cArrayExprNode : public cExprNode
{
public:
    cArrayExprNode(cExprNode *arrayExpr, cExprNode *indexExpr)
    {
        AddChild(arrayExpr);
        AddChild(indexExpr);
    }

    cExprNode* GetArray() { return dynamic_cast<cExprNode*>(GetChild(0)); }
    cExprNode* GetIndex() { return dynamic_cast<cExprNode*>(GetChild(1)); }

    cExprNode* GetBase();
    //cExprNode* GetIndex();

    virtual std::string NodeType() override
    {
        return "array";
    }

    /*virtual void Visit(cVisitor *visitor) override
    {
        visitor->Visit(this);
    }*/
    virtual cDeclNode* GetType()
    {
        return g_symbolTable.Find("char")->GetDecl();
    }
    /*void cSemanticVisitor::Visit(cArrayExprNode *node)
    {
        VisitAllChildren(node);

        cExprNode *base = node->GetBase();
        cExprNode *index = node->GetIndex();

        if (!base->GetType()->IsArray())
        {
            SemanticParseError(base->GetType()->GetName() +
            " is not an array");
        }
        if (!index->GetType()->IsInt())
        {
            SemanticParseError("Index of " +
            base->GetType()->GetName() +
            " is not an int");
        }
    }*/
};
