#pragma once
#include "cDeclNode.h"
#include "cSymbol.h"

class cArrayDeclNode : public cDeclNode
{
public:
    cArrayDeclNode(cSymbol *elemType, cSymbol *name, int count)
        : cDeclNode(), m_count(count)
    {
        AddChild(elemType);
        AddChild(name);
    }

    virtual std::string NodeType() override { return "array_decl"; }

    virtual std::string AttributesToString() override
    {
        return " count=\"" + std::to_string(m_count) + "\"";
    }

    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }
    virtual bool IsArray() { return true; }

    virtual cDeclNode* GetType()
    {
        cSymbol* typeSym = dynamic_cast<cSymbol*>(GetChild(0));
        return typeSym->GetDecl();
    }
private:
    int m_count;
};
