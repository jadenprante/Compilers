#include "cSemanticVisitor.h"
#include "cSymbolTable.h"
#include "cFuncDeclNode.h"
#include "cParamsNode.h"
#include "cSymbol.h"
#include <iostream>

extern cSymbolTable g_symbolTable;
extern void SemanticParseError(std::string error);

void cSemanticVisitor::VisitAllNodes(cAstNode *node)
{
    node->Visit(this);
}

void cSemanticVisitor::Visit(cAssignNode *node)
{
    node->VisitAllChildren(this);

    cDeclNode *lhsType = node->GetLhs()->GetType();
    cDeclNode *rhsType = node->GetRhs()->GetType();

    if (!lhsType->IsCompatibleWith(rhsType))
    {
        SemanticParseError("Cannot assign " +
            rhsType->GetName() + " to " +
            lhsType->GetName());
    }
}

void cSemanticVisitor::Visit(cVarExprNode *node)
{
    node->VisitAllChildren(this);

    cSymbol *sym = node->GetSymbol();
    if (sym == nullptr) return;

    cDeclNode *decl = sym->GetDecl();
    if (decl == nullptr) return;

    if (decl->IsFunc())
    {
        SemanticParseError("Symbol " +
            sym->GetName() +
            " is a function, not a variable");
    }
}

void cSemanticVisitor::Visit(cArrayExprNode *node)
{
    node->VisitAllChildren(this);

    cExprNode *base = node->GetBase();
    cExprNode *index = node->GetIndex();

    cDeclNode *baseType = base->GetType();
    cDeclNode *indexType = index->GetType();

    if (!baseType->IsArray())
    {
        SemanticParseError(baseType->GetName() +
            " is not an array");
    }

    if (!indexType->IsInt())
    {
        SemanticParseError("Index of " +
            baseType->GetName() +
            " is not an int");
    }
}

void cSemanticVisitor::Visit(cFuncCallNode *node)
{
    node->VisitAllChildren(this);

    cSymbol *sym = node->GetSymbol();
    if (sym == nullptr) return;

    cDeclNode *decl = sym->GetDecl();
    if (decl == nullptr) return;

    if (!decl->IsFunc())
        return;

    cFuncDeclNode *func =
        dynamic_cast<cFuncDeclNode*>(decl);

    if (func == nullptr)
        return;

    // Check number of arguments
    if (node->ArgCount() != func->ParamCount())
    {
        SemanticParseError(sym->GetName() +
            " called with wrong number of arguments");
        return;
    }

    // Check argument compatibility
    for (int i = 0; i < node->ArgCount(); i++)
    {
        cDeclNode *paramType =
            func->GetParam(i)->GetType();

        cDeclNode *argType =
            node->GetArg(i)->GetType();

        if (!paramType->IsCompatibleWith(argType))
        {
            SemanticParseError("function " +
                sym->GetName() +
                " called with incompatible argument");
        }
    }

    // Must be fully defined
    if (!func->HasDefinition())
    {
        SemanticParseError("Function " +
            sym->GetName() +
            " not fully defined");
    }
}

void cSemanticVisitor::Visit(cBinaryExprNode *node)
{
    node->VisitAllChildren(this);

    cDeclNode *left = node->GetLeft()->GetType();
    cDeclNode *right = node->GetRight()->GetType();

    // Relational and logical operators return int
    if (node->IsRelational() || node->IsLogical())
        return;

    // If incompatible arithmetic types
    if (!left->IsCompatibleWith(right) &&
        !right->IsCompatibleWith(left))
    {
        SemanticParseError("Incompatible types in binary expression");
    }
}

void cSemanticVisitor::Visit(cUnaryExprNode *node)
{
    node->VisitAllChildren(this);
}
