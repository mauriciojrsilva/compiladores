#include "functioncallnode.h"

FunctionCallNode::FunctionCallNode(const std::string& functionName, std::list<Node*>* children):
  Node("Chamada de funcao", children), functionName(functionName) {}

void FunctionCallNode::printSourceCode() {
  // TODO
}