//**************************************************************
// Implementation of the virtual Visitor class.
// This class must be subclassed (and made concrete) for all visitors
//

#include "cVisitor.h"
#include "cAstNode.h"
#include "cVisitor.h"
#include "cAstNode.h"     // base class
#include "cStmtNode.h"
#include "cBlockNode.h"
#include "cPrintNode.h"
#include "cReturnNode.h"
#include "cWhileNode.h"
#include "cExprNode.h"
#include "cIntExprNode.h"
#include "cFloatExprNode.h"
#include "cStringExprNode.h"
#include "cVarExprNode.h"
#include "cBinaryExprNode.h"
#include "cUnaryExprNode.h"
#include "cFuncExprNode.h"
#include "cArrayExprNode.h"
#include "cMemberExprNode.h"
#include "cOpNode.h"
#include "cDeclNode.h"
#include "cVarDeclNode.h"
#include "cArrayDeclNode.h"
#include "cStructDeclNode.h"
#include "cFuncDeclNode.h"
#include "cDeclsNode.h"
#include "cParamListNode.h"
#include "cStmtsNode.h"
#include "cProgramNode.h"
#include "cSymbol.h"
#include "cSymbol.h"   
#include <iostream>

void cVisitor::Visit(cAstNode* node)
{
    if (node != nullptr)
        node->Visit(this);  // calls the node's overridden Visit
}

// Statement Nodes
void cVisitor::Visit(cStmtNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cBlockNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cPrintNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cReturnNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cWhileNode* node) { if (node) node->Visit(this); }

// Expression Nodes
void cVisitor::Visit(cExprNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cIntExprNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cFloatExprNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cStringExprNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cVarExprNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cBinaryExprNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cUnaryExprNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cFuncExprNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cArrayExprNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cMemberExprNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cOpNode* node) { if (node) node->Visit(this); }

// Declaration Nodes
void cVisitor::Visit(cDeclNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cVarDeclNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cArrayDeclNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cStructDeclNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cFuncDeclNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cDeclsNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cParamListNode* node) { if (node) node->Visit(this); }

// Program / Statements
void cVisitor::Visit(cStmtsNode* node) { if (node) node->Visit(this); }
void cVisitor::Visit(cProgramNode* node) { if (node) node->Visit(this); }

// Symbols
void cVisitor::Visit(cSymbol* node) { if (node) node->Visit(this); }

// Utility: Visit all nodes recursively
void cVisitor::VisitAllNodes(cAstNode* node)
{
    if (node != nullptr)
        node->Visit(this);
}
