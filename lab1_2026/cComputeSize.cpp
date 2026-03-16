#include "cComputeSize.h"

#include "cProgramNode.h"
#include "cFuncDeclNode.h"
#include "cBlockNode.h"
#include "cVarDeclNode.h"
#include "cArrayDeclNode.h"
#include "cStructDeclNode.h"
#include "cDeclNode.h"

using namespace std;

static const int WORD_SIZE = 4;

//////////////////////////////////////////////////////////

cComputeSize::cComputeSize()
{
    m_offset = 0;
    m_highWater = 0;
}

//////////////////////////////////////////////////////////

int cComputeSize::Align(int size)
{
    if (size <= WORD_SIZE) return size;

    int remainder = size % WORD_SIZE;
    if (remainder == 0) return size;

    return size + (WORD_SIZE - remainder);
}

//////////////////////////////////////////////////////////
// PROGRAM
//////////////////////////////////////////////////////////

void cComputeSize::Visit(cProgramNode *node)
{
    node->VisitAllChildren(this);
}

//////////////////////////////////////////////////////////
// FUNCTION
//////////////////////////////////////////////////////////

void cComputeSize::Visit(cFuncDeclNode *node)
{
    int oldOffset = m_offset;
    int oldHighWater = m_highWater;

    m_offset = 0;
    m_highWater = 0;

    node->VisitAllChildren(this);

    node->SetSize(m_highWater);

    m_offset = oldOffset;
    m_highWater = oldHighWater;
}

//////////////////////////////////////////////////////////
// BLOCK
//////////////////////////////////////////////////////////

void cComputeSize::Visit(cBlockNode *node)
{
    int startOffset = m_offset;

    node->VisitAllChildren(this);

    int blockSize = m_offset - startOffset;

    if (m_offset > m_highWater)
        m_highWater = m_offset;

    m_offset = startOffset;
}

//////////////////////////////////////////////////////////
// VARIABLE DECL
//////////////////////////////////////////////////////////

void cComputeSize::Visit(cVarDeclNode *node)
{
    int size = WORD_SIZE;

    node->SetSize(size);
    node->SetOffset(m_offset);

    m_offset += size;

    if (m_offset > m_highWater)
        m_highWater = m_offset;
}

//////////////////////////////////////////////////////////
// ARRAY DECL
//////////////////////////////////////////////////////////

void cComputeSize::Visit(cArrayDeclNode *node)
{
    int elementSize = WORD_SIZE;
    int count = node->GetSize();   // array length from parser

    int size = elementSize * count;
    size = Align(size);

    node->SetSize(size);
    node->SetOffset(m_offset);

    m_offset += size;

    if (m_offset > m_highWater)
        m_highWater = m_offset;
}

//////////////////////////////////////////////////////////
// STRUCT DECL
//////////////////////////////////////////////////////////

void cComputeSize::Visit(cStructDeclNode *node)
{
    int oldOffset = m_offset;
    int oldHighWater = m_highWater;

    m_offset = 0;
    m_highWater = 0;

    node->VisitAllChildren(this);

    node->SetSize(m_highWater);

    m_offset = oldOffset;
    m_highWater = oldHighWater;
}
