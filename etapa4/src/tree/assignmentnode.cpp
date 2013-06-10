#include "assignmentnode.h"

AssignmentNode::AssignmentNode(const std::string& varName, Node* expressionAssigned):
  Node("Atribuicao"), varName(varName) {
  this->addChild(expressionAssigned);
}

AssignmentNode::AssignmentNode(const std::string& varName, Node* expressionIndex, Node* expressionAssigned):
  Node("Atribuicao"), varName(varName) {
  this->addChild(expressionIndex);
  this->addChild(expressionAssigned);
}

void AssignmentNode::printSourceCode() {}