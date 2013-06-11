#include "operationnode.h"
#include <stdio.h>

OperationNode::OperationNode(const Common::OperationType& operationType, Node* leftSide, Node* rightSide):
  ExpressionNode("Expressao operation"), operationType(operationType) {
  this->addChild(leftSide);
  this->addChild(rightSide);
}

void OperationNode::printSourceCode(const std::string& end) {
	if (this->children->size() == 2) {
		this->children->at(0)->printSourceCode("");
		fprintf(this->flexOut, "%s", " ");
		fprintf(this->flexOut, "%s", this->operationTypeToString(this->operationType).c_str());
		fprintf(this->flexOut, "%s", " ");
		this->children->at(1)->printSourceCode("");
	}
}
