#include "assignmentnode.h"
#include <stdio.h>

AssignmentNode::AssignmentNode(const std::string& varName, Node* expressionAssigned):
  Node("Atribuicao"), varName(varName) {
  this->addChild(expressionAssigned);
}

AssignmentNode::AssignmentNode(const std::string& varName, Node* expressionIndex, Node* expressionAssigned):
  Node("Atribuicao"), varName(varName) {
  this->addChild(expressionIndex);
  this->addChild(expressionAssigned);
}

void AssignmentNode::printSourceCode(const std::string& end) {
  if (this->children->size() == 1) {
    fprintf(this->flexOut, "%s", this->varName.c_str());
    fprintf(this->flexOut, "%s", " = ");
    this->children->at(0)->printSourceCode("");
    fprintf(this->flexOut, "%s", end.c_str());
  } else if (this->children->size() == 2) {
    fprintf(this->flexOut, "%s", this->varName.c_str());
    fprintf(this->flexOut, "%s", "[");
    this->children->at(0)->printSourceCode("");
    fprintf(this->flexOut, "%s", "]");
    fprintf(this->flexOut, "%s", " = ");
    this->children->at(1)->printSourceCode("");
    fprintf(this->flexOut, "%s", end.c_str());
  }
}