#include "functioncallnode.h"
#include <stdio.h>

FunctionCallNode::FunctionCallNode(const std::string& functionName, std::vector<Node*>* children):
  Node("Chamada de funcao", children), functionName(functionName) {}

void FunctionCallNode::printSourceCode(const std::string& end) {
  fprintf(this->flexOut, "%s", this->functionName.c_str());
  fprintf(this->flexOut, "%s", "(");
  for (std::vector<Node*>::iterator it = this->children->begin(); it != this->children->end(); it++)
    (*it)->printSourceCode("");
  fprintf(this->flexOut, "%s", ")");
  fprintf(this->flexOut, "%s", end.c_str());
}