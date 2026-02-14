#pragma once
#include <iomanip>
#include <sstream>
#include "cExprNode.h"

class cFloatExprNode : public cExprNode
{
public:
    explicit cFloatExprNode(double value) : cExprNode(), m_value(value) {}

    virtual std::string NodeType() override { return "float"; }

    virtual std::string AttributesToString() override
    {
        std::ostringstream out;
        out.setf(std::ios::fixed);
        out << std::setprecision(6) << m_value;
        return " value=\"" + out.str() + "\"";
    }

    virtual void Visit(cVisitor *visitor) override { visitor->Visit(this); }

private:
    double m_value;
};