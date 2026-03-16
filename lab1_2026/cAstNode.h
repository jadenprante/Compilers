//**************************************
// cAstNode.h
//
// pure virtual base class for all AST nodes
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
//

#pragma once
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

#include "cVisitor.h"

// Defined in lex.h but declared here to avoid circular includes
extern int yylineno;
extern int yynerrs;

// Semantic error routine
void SemanticParseError(std::string error);

class cAstNode
{
public:
    //*************************************
    // Constructor
    cAstNode() : m_LineNum(yylineno), m_hasSemanticError(false) {}

    //*************************************
    // Convert AST to XML string
    string ToString()
    {
        return ToStringImpl(0, true);
    }

    //*************************************
    // Print semantic error
    void SemanticError(string message)
    {
        std::cout << "ERROR: " << message
                  << " near line " << m_LineNum << "\n";
        yynerrs++;
        m_hasSemanticError = true;
    }

    //*************************************
    // Check for semantic errors in subtree
    bool HasSemanticError()
    {
        if (m_hasSemanticError)
            return true;

        for (auto child : m_children)
        {
            if (child != nullptr && child->HasSemanticError())
                return true;
        }
        return false;
    }

    //*************************************
    // Visitor entry point
    virtual void Visit(cVisitor *visitor) = 0;

    //*************************************
    // Visit all children (used by visitors)
    void VisitAllChildren(cVisitor* visitor)
    {
        for (auto child : m_children)
        {
            if (child != nullptr)
                child->Visit(visitor);
        }
    }

    //*************************************
    // Child access for visitors
    cAstNode* GetChild(int child)
    {
        if (child >= (int)m_children.size())
            return nullptr;

        return m_children[child];
    }

    int NumChildren() const
    {
        return (int)m_children.size();
    }

protected:
    //*************************************
    // Add child
    void AddChild(cAstNode *child)
    {
        m_children.push_back(child);
    }

    //*************************************
    // Copy children from another node
    void AddAllChildren(cAstNode *node)
    {
        if (node != nullptr && node->HasChildren())
        {
            for (auto child : node->m_children)
            {
                AddChild(child);
            }
        }
    }

    //*************************************
    bool HasChildren() const
    {
        return !m_children.empty();
    }

    //*************************************
    void SetChild(int index, cAstNode *child)
    {
        m_children[index] = child;
    }

    //*************************************
    // Node type for XML
    virtual string NodeType() = 0;

    //*************************************
    // Optional attributes
    virtual string AttributesToString()
    {
        return "";
    }

private:
    //*************************************
    // Internal recursive XML builder
    string ToStringImpl(int indent, bool isRoot)
    {
        string result;

        if (isRoot && NodeType() == "program")
            result += "<?xml version=\"1.0\"?>\n";

        result.append(indent * 2, ' ');
        result += "<" + NodeType();
        result += AttributesToString();

        if (HasChildren())
        {
            result += ">\n";

            for (auto child : m_children)
            {
                if (child != nullptr)
                    result += child->ToStringImpl(indent + 1, false);
            }

            result.append(indent * 2, ' ');
            result += "</" + NodeType() + ">\n";
        }
        else
        {
            result += "/>\n";
        }

        return result;
    }

private:
    vector<cAstNode *> m_children;
    int m_LineNum;
    bool m_hasSemanticError;
};