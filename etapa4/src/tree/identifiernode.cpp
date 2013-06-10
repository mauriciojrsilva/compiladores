#include "identifiernode.h"
#include <stdio.h>

IdentifierNode::IdentifierNode(Symbol* symbol):
  ExpressionNode("Expressao idenficador"), symbol(symbol) {
  // TODO check the data type
}

IdentifierNode::IdentifierNode(Symbol* symbol, Node* expression):
  ExpressionNode("Expressao idenficador"), symbol(symbol) {
  // TODO check the data type
}

void IdentifierNode::printSourceCode(const std::string& end) {
  fprintf(this->flexOut, "%s", symbol->getText().c_str());
}