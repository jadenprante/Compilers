#include "cCodeGenVisitor.h"

#include "emit.h"

#include "cProgramNode.h"
#include "cFuncDeclNode.h"
#include "cBlockNode.h"
#include "cAssignNode.h"
#include "cVarExprNode.h"
#include "cBinaryExprNode.h"
#include "cIntExprNode.h"
#include "cFuncCallNode.h"
#include "cPrintNode.h"
#include "cDeclNode.h"

using namespace std;

// INPUT
cCodeGenVisitor::cCodeGenVisitor(std::string filename)
{
    InitOutput(filename);
}

// DECONSTRUCTOR & OUTPUT
cCodeGenVisitor::~cCodeGenVisitor()
{
    FinalizeOutput();
}

// PROGRAM
void cCodeGenVisitor::Visit(cProgramNode *node)
{
    node->VisitAllChildren(this);
}

// FUNCTION
void cCodeGenVisitor::Visit(cFuncDeclNode *node)
{
    EmitString(".function ");
    EmitString(node->GetName());
    EmitString("\n");

    EmitString(node->GetName());
    EmitString(":\n");

    node->VisitAllChildren(this);

    EmitString("PUSH 0\n");
    EmitString("RETURNV\n");
}

// BLOCK
void cCodeGenVisitor::Visit(cBlockNode *node)
{
    node->VisitAllChildren(this);
}

// INTEGER CONSTANT
void cCodeGenVisitor::Visit(cIntExprNode *node)
{
    EmitString("PUSH ");
    EmitInt(node->GetValue());
    EmitString("\n");
}

// VARIABLE LOAD
void cCodeGenVisitor::Visit(cVarExprNode *node)
{
    int offset = node->GetSymbol()->GetDecl()->GetOffset();

    EmitString("PUSHVAR ");
    EmitInt(offset);
    EmitString("\n");
}

// ASSIGNMENT
void cCodeGenVisitor::Visit(cAssignNode *node)
{
    cVarExprNode *var =
        dynamic_cast<cVarExprNode*>(node->GetChild(0));

    cExprNode *expr =
        dynamic_cast<cExprNode*>(node->GetChild(1));

    int offset = var->GetSymbol()->GetDecl()->GetOffset();

    expr->Visit(this);

    EmitString("POPVAR ");
    EmitInt(offset);
    EmitString("\n");
}

// BINARY EXPRESSION
void cCodeGenVisitor::Visit(cBinaryExprNode *node)
{
    node->GetLeft()->Visit(this);
    node->GetRight()->Visit(this);

    string op = node->GetOp();

    if (op == "+")
        EmitString("PLUS\n");
    else if (op == "-")
        EmitString("MINUS\n");
    else if (op == "*")
        EmitString("TIMES\n");
    else if (op == "/")
        EmitString("DIVIDE\n");
    else if (op == "%")
        EmitString("MOD\n");
    else if (op == "<")
        EmitString("LT\n");
    else if (op == ">")
        EmitString("GT\n");
    else if (op == "==")
        EmitString("EQ\n");
    else if (op == "!=")
        EmitString("NE\n");
}

// FUNCTION CALL
void cCodeGenVisitor::Visit(cFuncCallNode *node)
{
    int numArgs = node->NumArgs();

    for (int i = 0; i < numArgs; i++)
    {
        node->GetArg(i)->Visit(this);
    }

    EmitString("CALL @");
    EmitString(node->GetName());
    EmitString("\n");

    for (int i = 0; i < numArgs; i++)
    {
        EmitString("SWAP\n");
        EmitString("POP\n");
    }
}

// PRINT
void cCodeGenVisitor::Visit(cPrintNode *node)
{
    node->GetExpr()->Visit(this);

    EmitString("CALL @print\n");

    EmitString("SWAP\n");
    EmitString("POP\n");
}
