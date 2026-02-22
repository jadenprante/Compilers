//**************************************************************
// Implementation of the virtual Visitor class.
// This class must be subclassed (and made concrete) for all visitors
//

#include "lex.h"
#include "astnodes.h"
#include "cVisitor.h"

//******************************************
// All AST node types need a Visit method. 
// The code for each method is identical: simply visit all children
void cVisitor::Visit(cAstNode* node)        { node->VisitAllChildren(this); }
void cVisitor::Visit(cBlockNode* node)      { node->VisitAllChildren(this); }
void cVisitor::Visit(cDeclNode* node)       { node->VisitAllChildren(this); }
void cVisitor::Visit(cDeclsNode* node)      { node->VisitAllChildren(this); }
void cVisitor::Visit(cExprNode* node)       { node->VisitAllChildren(this); }
void cVisitor::Visit(cIntExprNode* node)    { node->VisitAllChildren(this); }
void cVisitor::Visit(cOpNode* node)         { node->VisitAllChildren(this); }
void cVisitor::Visit(cPrintNode* node)      { node->VisitAllChildren(this); }
void cVisitor::Visit(cProgramNode* node)    { node->VisitAllChildren(this); }
void cVisitor::Visit(cStmtNode* node)       { node->VisitAllChildren(this); }
void cVisitor::Visit(cStmtsNode* node)      { node->VisitAllChildren(this); }
void cVisitor::Visit(cSymbol* node)         { node->VisitAllChildren(this); }
void cVisitor::Visit(cFuncDeclNode* node)   { node->VisitAllChildren(this); }
void cVisitor::Visit(cFuncExprNode* node)   { node->VisitAllChildren(this); }
void cVisitor::Visit(cParamListNode* node)  { node->VisitAllChildren(this); }
void cVisitor::Visit(cUnaryExprNode* node)  { node->VisitAllChildren(this); }
void cVisitor::Visit(cWhileNode* node)      { node->VisitAllChildren(this); }
void cVisitor::Visit(cReturnNode* node)     { node->VisitAllChildren(this); }
void cVisitor::Visit(cVarExprNode* node)    { node->VisitAllChildren(this); }
void cVisitor::Visit(cBinaryExprNode* node) { node->VisitAllChildren(this); }
void cVisitor::Visit(cStringExprNode* node) { node->VisitAllChildren(this); }
void cVisitor::Visit(cMemberExprNode* node) { node->VisitAllChildren(this); }
void cVisitor::Visit(cArrayExprNode* node)  { node->VisitAllChildren(this); }
void cVisitor::VisitAllNodes(cAstNode *node)
{
    node->Visit(this);
}
