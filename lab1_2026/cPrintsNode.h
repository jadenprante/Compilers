#pragma once
#include <string>
#include "cStmtNode.h"

class cPrintsNode : public cStmtNode
{
public:
    explicit cPrintsNode(const std::string &value) : cStmtNode(), m_value(value) {}

    virtual std::string NodeType() override { return "prints"; }

    virtual std::string AttributesToString() override
    {
        return " value=\"" + m_value + "\"";
    }

    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }

private:
    std::string m_value;
};