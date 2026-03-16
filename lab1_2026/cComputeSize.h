#pragma once

#include "cVisitor.h"

class cProgramNode;
class cFuncDeclNode;
class cBlockNode;
class cDeclNode;
class cVarDeclNode;
class cArrayDeclNode;
class cStructDeclNode;

class cComputeSize : public cVisitor
{
public:
    cComputeSize();

    virtual void Visit(cProgramNode *node) override;
    virtual void Visit(cFuncDeclNode *node) override;
    virtual void Visit(cBlockNode *node) override;

    virtual void Visit(cVarDeclNode *node);
    virtual void Visit(cArrayDeclNode *node);
    virtual void Visit(cStructDeclNode *node);

private:
    int m_offset;       // current stack offset
    int m_highWater;    // max stack usage for this scope

    int Align(int size);
};
