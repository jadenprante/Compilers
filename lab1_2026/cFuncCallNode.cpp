#include "cFuncCallNode.h"

cExprNode* cFuncCallNode::GetArg(int index)
{
    return dynamic_cast<cExprNode*>(GetChild(index));
}
