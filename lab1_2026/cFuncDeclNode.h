#pragma once

#include "cDeclNode.h"
#include "cSymbol.h"
#include "cParamsNode.h"
#include "cDeclsNode.h"
#include "cStmtsNode.h"
#include "cVisitor.h"

class cFuncDeclNode : public cDeclNode
{
private:
    cSymbol *m_type;
    cSymbol *m_name;
    cParamsNode *m_params;
    cDeclsNode *m_locals;
    cStmtsNode *m_stmts;

public:
    cFuncDeclNode(cSymbol *type, cSymbol *name,
                  cParamsNode *params, cDeclsNode *locals,
                  cStmtsNode *stmts)
        : m_type(type), m_name(name),
          m_params(params), m_locals(locals), m_stmts(stmts)
    {
        // Add children for visitor traversal
        AddChild(m_type);
        AddChild(m_name);
        AddChild(m_params);
        AddChild(m_locals);
        AddChild(m_stmts);
    }

    virtual string NodeType() override { return "funcdecl"; }
    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
};
