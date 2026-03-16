#pragma once

#include "cVisitor.h"
#include "emit.h"

class cProgramNode;
class cFuncDeclNode;
class cBlockNode;
class cAssignNode;
class cVarExprNode;
class cBinaryExprNode;
class cIntExprNode;
class cFuncCallNode;
class cPrintNode;

class cCodeGenVisitor : public cVisitor
{
public:
    cCodeGenVisitor(std::string filename);
    virtual ~cCodeGenVisitor();

    virtual void Visit(cProgramNode *node) override;
    virtual void Visit(cFuncDeclNode *node) override;
    virtual void Visit(cBlockNode *node) override;

    virtual void Visit(cAssignNode *node);

    virtual void Visit(cVarExprNode *node) override;
    virtual void Visit(cIntExprNode *node) override;
    virtual void Visit(cBinaryExprNode *node) override;

    virtual void Visit(cFuncCallNode *node);
    virtual void Visit(cPrintNode *node) override;
};
