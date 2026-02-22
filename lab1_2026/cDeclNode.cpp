#include "cDeclNode.h"
#include "cBaseTypeNode.h"

bool cDeclNode::IsCompatibleWith(cDeclNode *type)
{
    if (this == type) return true;

    cBaseTypeNode *left = dynamic_cast<cBaseTypeNode*>(this);
    cBaseTypeNode *right = dynamic_cast<cBaseTypeNode*>(type);

    if (left && right)
    {
        if (left->IsFloat() && right->IsInt()) return true;
        if (left->IsFloat() && right->IsFloat()) return true;
        if (left->IsInt() && right->IsInt()) return true;
    }

    return false;
}
