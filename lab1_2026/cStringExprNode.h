#pragma once
#include "cExprNode.h"
#include <string>

class cStringExprNode : public cExprNode
{
public:
    cStringExprNode(const std::string &value)
        : m_value(value)
    {
    }

    virtual std::string NodeType() override
    {
        return "string";
    }

    virtual std::string AttributesToString() override
    {
        return " value=\"" + m_value + "\"";
    }

    virtual void Visit(cVisitor *visitor) override
    {
        visitor->Visit(this);
    }

private:
    std::string m_value;
};
