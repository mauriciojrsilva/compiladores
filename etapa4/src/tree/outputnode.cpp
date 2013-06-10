#include "outputnode.h"

OutputNode::OutputNode(std::list<Node*>* children): Node("Saida", children) {}

void OutputNode::printSourceCode() {}