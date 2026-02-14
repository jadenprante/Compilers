//**************************************
// cOpNode.h
//
// Class for an operator (e.g. + - etc.)
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#pragma once
#include "cAstNode.h"
#include "langparse.h"

/*#define NOT_EQUALS 256
#define EQUALS     257
#define OR         258
#define AND        259
#define GE         260
#define LE         261*/


class cOpNode : public cAstNode
{
    public:
        cOpNode(int op) : cAstNode()
        {
            m_op = op;
        }

        int GetOp() { return m_op; }

        virtual string NodeType()       { return "op"; }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        string GetOpAsString()
        {
            string result("");

            switch (m_op)
            {
                case NOT_EQUALS:
                    result += "!=";
                    break;
                case EQUALS:
                    result += "==";
                    break;
                case OR:
                    result += "||";
                    break;
                case AND:
                    result += "AND";
                    break;
                case GE:
                    result += "GE";
                    break;
                case '>':
                    result += "GT";
                    break;
                case LE:
                    result += "LE";
                    break;
                case '<':
                    result += "LT";
                    break;
                default:
                    result += (char)m_op;
                    break;
            }

            return result;
        }
        virtual string AttributesToString()   
        { 
            string result(" value='");

            result += GetOpAsString();

            result += "'";

            return result;
        }
    protected:
        int m_op;      // the operand
};

