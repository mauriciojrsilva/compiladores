#ifndef TYPENODE_H
#define TYPENODE_H

#include "node.h"
#include "common.h"

class TypeNode : public Node
{
public:
    TypeNode(Common::DataType dataType);
    Common::DataType getType();

private:
    Common::DataType dataType;
};

#endif // TYPENODE_H
