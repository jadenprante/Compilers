#include "cComputeSizeVisitor.h"

#include "cProgramNode.h"
#include "cBlockNode.h"
#include "cVarDeclNode.h"
#include "cArrayDeclNode.h"
#include "cStructDeclNode.h"
#include "cFuncDeclNode.h"
#include "cVarExprNode.h"
#include "cArrayExprNode.h"
#include "cDeclNode.h"

cComputeSizeVisitor::cComputeSizeVisitor()
{
}

// Helper Functions
void cComputeSizeVisitor::EnterScope()
{
    m_offsetStack.push_back(0);
    m_highWaterStack.push_back(0);
}

void cComputeSizeVisitor::ExitScope(cAstNode *node)
{
    int high = m_highWaterStack.back();

    // If node has size (block, struct, func)
    cBlockNode *block = dynamic_cast<cBlockNode*>(node);
    if (block != nullptr)
        block->SetSize(high);

    cStructDeclNode *str = dynamic_cast<cStructDeclNode*>(node);
    if (str != nullptr)
        str->SetSize(high);

    cFuncDeclNode *func = dynamic_cast<cFuncDeclNode*>(node);
    if (func != nullptr)
        func->SetSize(high);

    m_offsetStack.pop_back();
    m_highWaterStack.pop_back();
}

int cComputeSizeVisitor::Align(int size)
{
    if (size <= 1) return size;

    int rem = size % WORD_SIZE;
    if (rem == 0) return size;

    return size + (WORD_SIZE - rem);
}

// Program
void cComputeSizeVisitor::Visit(cProgramNode *node)
{
    EnterScope();
    node->VisitAllChildren(this);
    ExitScope(node);
}

// Block
void cComputeSizeVisitor::Visit(cBlockNode *node)
{
    EnterScope();
    node->VisitAllChildren(this);
    ExitScope(node);
}

// Variable Declaration
void cComputeSizeVisitor::Visit(cVarDeclNode *node)
{
    int size = node->GetType()->GetSize();
    size = Align(size);

    int offset = m_offsetStack.back();

    node->SetSize(size);
    node->SetOffset(offset);

    m_offsetStack.back() += size;

    if (m_offsetStack.back() > m_highWaterStack.back())
        m_highWaterStack.back() = m_offsetStack.back();
}

// Array Declaration (1D only)
void cComputeSizeVisitor::Visit(cArrayDeclNode *node)
{
    int baseSize = node->GetType()->GetSize();
    int count = node->GetCount();   // must exist in your class

    int size = Align(baseSize * count);

    int offset = m_offsetStack.back();

    node->SetSize(size);
    node->SetOffset(offset);

    m_offsetStack.back() += size;

    if (m_offsetStack.back() > m_highWaterStack.back())
        m_highWaterStack.back() = m_offsetStack.back();
}

// Struct Declaration
void cComputeSizeVisitor::Visit(cStructDeclNode *node)
{
    EnterScope();

    node->VisitAllChildren(this);

    int structSize = m_highWaterStack.back();
    node->SetSize(structSize);

    ExitScope(node);
}

// Function Declaration
void cComputeSizeVisitor::Visit(cFuncDeclNode *node)
{
    EnterScope();

    node->VisitAllChildren(this);

    int funcSize = m_highWaterStack.back();
    node->SetSize(funcSize);

    ExitScope(node);
}

// Variable Expression
void cComputeSizeVisitor::Visit(cVarExprNode *node)
{
    cDeclNode *decl = node->GetSymbol()->GetDecl();

    node->SetSize(decl->GetSize());
    node->SetOffset(decl->GetOffset());
}

// Array Expression (1D only)
void cComputeSizeVisitor::Visit(cArrayExprNode *node)
{
    cDeclNode *decl = node->GetSymbol()->GetDecl();

    node->SetOffset(decl->GetOffset());

    int elementSize = decl->GetType()->GetSize();
    elementSize = Align(elementSize);

    node->SetSize(elementSize);

    node->AddRowSize(elementSize);
}
