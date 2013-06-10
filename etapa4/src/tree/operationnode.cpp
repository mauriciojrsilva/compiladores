#include "operationnode.h"

OperationNode::OperationNode(const Common::OperationType& operationType, Node* leftSide, Node* rightSide):
  ExpressionNode("Expressao operation"), operationType(operationType) {
  this->addChild(leftSide);
  this->addChild(rightSide);
}

void OperationNode::printSourceCode(const std::string& end) {
  // TODO
}