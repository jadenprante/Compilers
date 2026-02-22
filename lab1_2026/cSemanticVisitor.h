#pragma once

#include "cVisitor.h"
#include "cAssignNode.h"
#include "cVarExprNode.h"
#include "cArrayExprNode.h"
#include "cFuncCallNode.h"
#include "cBinaryExprNode.h"
#include "cUnaryExprNode.h"
#include "cDeclNode.h"

class cSemanticVisitor : public cVisitor
{
public:
    cSemanticVisitor() {}

    // === Required semantic checks ===
    virtual void Visit(cAssignNode *node);
    virtual void Visit(cVarExprNode *node);
    virtual void Visit(cArrayExprNode *node);
    virtual void Visit(cFuncCallNode *node);
    virtual void Visit(cBinaryExprNode *node);
    virtual void Visit(cUnaryExprNode *node);

    // Everything else just traverses
    virtual void VisitAllNodes(cAstNode *node) override;
};
