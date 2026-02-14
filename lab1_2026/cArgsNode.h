#pragma once
#include "cAstNode.h"
#include "cDeclNode.h"

class cArgsNode : public cAstNode
{
public:
    cArgsNode() : cAstNode() {}
    explicit cArgsNode(cDeclNode *first) : cAstNode() { AddChild(first); }

    void Insert(cDeclNode *decl) { AddChild(decl); }

    virtual std::string NodeType() override { return "args"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};