#include "outputnode.h"

OutputNode::OutputNode(std::vector<Node*>* children): Node("Saida", children) {}

void OutputNode::printSourceCode(const std::string& end) {}