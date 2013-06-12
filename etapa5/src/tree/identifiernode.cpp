#include "identifiernode.h"
#include <stdio.h>

IdentifierNode::IdentifierNode(Symbol* symbol):
  ExpressionNode("Expressao idenficador"), symbol(symbol) {
  // TODO check the data type
}

IdentifierNode::IdentifierNode(Symbol* symbol, Node* expression):
  ExpressionNode("Expressao idenficador"), symbol(symbol) {
  // TODO check the data type
	this->addChild(expression);
}

void IdentifierNode::printSourceCode(const std::string& end) {
	if (this->children->size() == 0)
		fprintf(this->flexOut, "%s", symbol->getText().c_str());
	else if (this->children->size() == 1) {
		fprintf(this->flexOut, "%s", symbol->getText().c_str());
		fprintf(this->flexOut, "%s", "[");
		this->children->at(0)->printSourceCode("");
		fprintf(this->flexOut, "%s", "]");
	}
}
