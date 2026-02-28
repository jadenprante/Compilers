#pragma once

#include "cVisitor.h"
#include <vector>

class cComputeSizeVisitor : public cVisitor
{
public:
    cComputeSizeVisitor();

    virtual void Visit(cProgramNode *node) override;
    virtual void Visit(cBlockNode *node) override;

    virtual void Visit(cVarDeclNode *node) override;
    virtual void Visit(cArrayDeclNode *node) override;
    virtual void Visit(cStructDeclNode *node) override;
    virtual void Visit(cFuncDeclNode *node) override;

    virtual void Visit(cVarExprNode *node) override;
    virtual void Visit(cArrayExprNode *node) override;

private:
    static const int WORD_SIZE = 4;

    std::vector<int> m_offsetStack;
    std::vector<int> m_highWaterStack;

    void EnterScope();
    void ExitScope(cAstNode *node);

    int Align(int size);
};
