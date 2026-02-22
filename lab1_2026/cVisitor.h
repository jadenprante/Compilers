//*******************************************************
// Declaration of the visitor class.
// This class is used to implement the visitor pattern.
//
// As you add AST node types, you must add the forward declaration and
// the virtual Visit function.
// Lab 4 will work without this, BUT Lab 5 will go more smoothly if you
// keep this class current with all your AST node types.

#pragma once
//#include "cArrayExprNode.h"
class cAstNode; 
class cBlockNode; 
class cDeclNode; 
class cDeclsNode; 
class cExprNode;
class cIntExprNode;
class cOpNode; 
class cPrintNode;
class cProgramNode; 
class cStmtNode;
class cStmtsNode; 
class cSymbol; 
class cFuncDeclNode; 
class cFuncExprNode; 
class cParamListNode;
class cUnaryExprNode; 
class cWhileNode; 
class cReturnNode; 
class cVarExprNode; 
class cBinaryExprNode;
class cStringExprNode;
class cMemberExprNode;
class cArrayExprNode;


class cVisitor
{
public:
    virtual void VisitAllNodes(cAstNode* node);
    virtual void Visit(cAstNode* node);
    virtual void Visit(cBlockNode* node);
    virtual void Visit(cDeclNode* node);
    virtual void Visit(cDeclsNode* node);
    virtual void Visit(cExprNode* node);
    virtual void Visit(cIntExprNode* node);
    virtual void Visit(cOpNode* node);
    virtual void Visit(cPrintNode* node);
    virtual void Visit(cProgramNode* node);
    virtual void Visit(cStmtNode* node);
    virtual void Visit(cStmtsNode* node);
    virtual void Visit(cSymbol* node);

    virtual void Visit(cFuncDeclNode* node);
    virtual void Visit(cFuncExprNode* node);
    virtual void Visit(cParamListNode* node);
    virtual void Visit(cUnaryExprNode* node);
    virtual void Visit(cWhileNode* node);
    virtual void Visit(cReturnNode* node);
    virtual void Visit(cVarExprNode* node);
    virtual void Visit(cBinaryExprNode* node);
    virtual void Visit(cStringExprNode* node);
    virtual void Visit(cMemberExprNode* node);
    virtual void Visit(cArrayExprNode* node);

};
