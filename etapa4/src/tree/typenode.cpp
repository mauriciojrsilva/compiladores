#include "typenode.h"

TypeNode::TypeNode(Common::DataType dataType): dataType(dataType) {}

Common::DataType TypeNode::getType() {
    return this->dataType;
}