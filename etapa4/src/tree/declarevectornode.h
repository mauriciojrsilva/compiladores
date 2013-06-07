#ifndef DECLAREVECTORNODE_H
#define DECLAREVECTORNODE_H

#include "node.h"
#include "common.h"

class DeclareVectorNode : public Node
{
public:
    DeclareVectorNode(Common::DataType dataType, int size);

private:
    Common::DataType dataType;
};

#endif // DECLAREVECTORNODE_H
