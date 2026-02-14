//**************************************
// astnodes.h
//
// Single place that includes all the ast nodes.
// Useful for lang.y and lang.l
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2015
//

#pragma once
#include "cAstNode.h"
#include "cProgramNode.h"
#include "cBlockNode.h"
#include "cStmtNode.h"
#include "cStmtsNode.h"

#include "cExprNode.h"
#include "cIntExprNode.h"
#include "cFloatExprNode.h"
#include "cBinaryExprNode.h"
#include "cUnaryExprNode.h"
#include "cOpNode.h"
#include "cVarExprNode.h"
#include "cFuncExprNode.h"
#include "cArrayExprNode.h"     // needed for expr '[' expr ']'
#include "cMemberExprNode.h"    // needed for expr '.' IDENTIFIER
#include "cFuncCallNode.h"      // needed for IDENTIFIER '(' param_list ')'

#include "cPrintNode.h"
#include "cPrintsNode.h"
#include "cAssignNode.h"
#include "cReturnNode.h"
#include "cWhileNode.h"
#include "cIfNode.h"

#include "cDeclNode.h"
#include "cDeclsNode.h"
#include "cVarDeclNode.h"
#include "cArrayDeclNode.h"
#include "cStructDeclNode.h"
#include "cFuncDeclNode.h"

#include "cParamsNode.h"
#include "cParamListNode.h"
