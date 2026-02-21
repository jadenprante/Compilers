#pragma once
#include "cDeclNode.h"
#include "cSymbol.h"
#include "cParamsNode.h"
#include "cDeclsNode.h"
#include "cStmtsNode.h"
#include "cSymbolTable.h"

extern cSymbolTable g_symbolTable;
void SemanticParseError(std::string error);

class cFuncDeclNode : public cDeclNode
{
public:
    cFuncDeclNode(cSymbol *type, cSymbol *name,
                  cParamsNode *params,
                  cDeclsNode *locals,
                  cStmtsNode *stmts)
        : m_hasDefinition(stmts != nullptr)
    {
        cSymbol* existing = g_symbolTable.FindLocal(name->GetName());

        if (existing && !existing->GetDecl()->IsFunc())
        {
            SemanticParseError("Symbol " + name->GetName() +
                               " already defined in current scope");
            return;
        }

        if (!existing)
        {
            g_symbolTable.Insert(name);
            name->SetDecl(this);
        }

        AddChild(type);
        AddChild(name);
        AddChild(params);
        AddChild(locals);
        AddChild(stmts);
    }

    virtual string NodeType() override { return "funcdecl"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
    virtual bool IsFunc() { return true; }

    virtual cDeclNode* GetType()
    {
        return dynamic_cast<cSymbol*>(GetChild(0))->GetDecl();
    }

private:
    bool m_hasDefinition;
};