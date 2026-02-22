#include "cBinaryExprNode.h"
#include "cSymbolTable.h"

extern cSymbolTable g_symbolTable;

cDeclNode* cBinaryExprNode::GetType()
{
    cDeclNode *leftType = GetLeft()->GetType();
    cDeclNode *rightType = GetRight()->GetType();

    std::string op = GetOpNode()->GetOp();

    // Relational operators
    if (op == ">"  || op == "<"  ||
        op == ">=" || op == "<=" ||
        op == "==" || op == "!=")
    {
        return g_symbolTable.Find("int")->GetDecl();
    }

    // Logical operators
    if (op == "||" || op == "&&")
    {
        return g_symbolTable.Find("int")->GetDecl();
    }

    // Type promotion rules
    if (leftType->IsFloat() || rightType->IsFloat())
        return g_symbolTable.Find("float")->GetDecl();

    if (leftType->IsInt() || rightType->IsInt())
        return g_symbolTable.Find("int")->GetDecl();

    return g_symbolTable.Find("char")->GetDecl();
}
