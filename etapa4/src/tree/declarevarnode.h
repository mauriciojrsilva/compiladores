#ifndef DECLAREVARNODE_H
#define DECLAREVARNODE_H

#include "node.h"
#include "common.h"

class DeclareVarNode : public Node
{
public:
    DeclareVarNode(Common::DataType dataType);

private:
    Common::DataType dataType;
};

#endif // DECLAREVARNODE_H
