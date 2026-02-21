//********************************************************
// cSymbol.h - Define a class for symbols
//
// Author: Philip Howard
//
#pragma once
#include "cAstNode.h"
#include "cDeclNode.h"
#include <string>

using std::string;

class cSymbol : public cAstNode
{
public:
    cSymbol(const string &name)
        : cAstNode(), m_name(name), m_decl(nullptr)
    {
        m_id = ++nextId;
    }

    string GetName() const { return m_name; }
    int GetId() const { return m_id; }

    void SetDecl(cDeclNode* decl) { m_decl = decl; }
    cDeclNode* GetDecl() { return m_decl; }

    virtual string NodeType() override { return "sym"; }

    virtual string AttributesToString() override
    {
        return " id=\"" + std::to_string(m_id) +
               "\" name=\"" + m_name + "\"";
    }

    virtual void Visit(cVisitor *visitor) override
    {
        visitor->Visit(this);
    }

    static long long nextId;

private:
    long long m_id;
    string m_name;
    cDeclNode* m_decl;
};

