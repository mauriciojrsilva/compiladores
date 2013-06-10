#include "ifnode.h"

IfNode::IfNode(Node* expression, Node* commandThen): Node("Se") {
  this->addChild(expression);
  this->addChild(commandThen);
}

IfNode::IfNode(Node* expression, Node* commandThen, Node* commandElse): Node("Se Senao") {
  this->addChild(expression);
  this->addChild(commandThen);
  this->addChild(commandElse);
}

void IfNode::printSourceCode(const std::string& end) {}