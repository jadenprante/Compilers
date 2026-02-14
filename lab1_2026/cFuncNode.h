#pragma once
#include "cDeclNode.h"
#include "cSymbol.h"
#include "cArgsNode.h"
#include "cDeclsNode.h"
#include "cStmtsNode.h"

class cFuncNode : public cDeclNode
{
public:
    cFuncNode(cSymbol *returnType, cSymbol *name, cArgsNode *args = nullptr,
              cDeclsNode *decls = nullptr, cStmtsNode *stmts = nullptr)
        : cDeclNode()
    {
        AddChild(returnType);
        AddChild(name);
        AddChild(args);
        AddChild(decls);
        AddChild(stmts);
    }

    virtual std::string NodeType() override { return "func"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};