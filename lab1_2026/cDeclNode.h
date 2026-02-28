//**************************************
// cDeclNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#pragma once
#include "cAstNode.h"

class cDeclNode : public cAstNode
{
public:
    cDeclNode() : cAstNode() {}

    virtual bool IsArray()  { return false; }
    virtual bool IsStruct() { return false; }
    virtual bool IsType()   { return false; }
    virtual bool IsFunc()   { return false; }
    virtual bool IsVar()    { return false; }

    virtual bool IsFloat()  { return false; }
    virtual bool IsInt()    { return false; }
    virtual bool IsChar()   { return false; }

    virtual int  GetSize()  { return m_size; }
    virtual void SetSize(int size) { m_size = size; }

    virtual int GetOffset() const { return m_offset; }
    virtual void SetOffset(int offset) { m_offset = offset; }

    virtual cDeclNode* GetType() = 0;
    virtual string GetName() = 0;

    bool IsCompatibleWith(cDeclNode *type);
private:
    int m_size = 0;
    int m_offset = 0;

};
