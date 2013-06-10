#include "blocknode.h"

BlockNode::BlockNode(std::list<Node*>* children): Node("Bloco", children) {}

void BlockNode::printSourceCode() {}