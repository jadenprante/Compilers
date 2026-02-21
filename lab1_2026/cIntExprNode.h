//**************************************
// cIntExprNode.h
//
// Defines an AST node for an integer constant (literals).
//
// Inherits from cExprNode so that integer constants can be used anywhere 
// expressions are used.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#pragma once
#include "cExprNode.h"
#include "cSymbolTable.h"

extern cSymbolTable g_symbolTable;

class cIntExprNode : public cExprNode
{
public:
    cIntExprNode(int value) : m_value(value) {}

    virtual string AttributesToString()
    {
        return " value=\"" + std::to_string(m_value) + "\"";
    }

    virtual string NodeType() { return "int"; }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    virtual cDeclNode* GetType()
    {
        if (m_value >= 0 && m_value <= 127)
        {
            return g_symbolTable.Find("char")->GetDecl();
        }
        else
        {
            return g_symbolTable.Find("int")->GetDecl();
        }
    }

private:
    int m_value;
};