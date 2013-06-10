#include "headernode.h"
#include <iostream>

HeaderNode::HeaderNode(const std::string &functionName, Common::DataType dataType, std::list<Node *> *children):
  Node("Cabecalho", children), functionName(functionName), dataType(dataType) {}


void HeaderNode::printSourceCode() {
  // TODO
}