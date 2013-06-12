#include "ifnode.h"
#include <stdio.h>

IfNode::IfNode(Node* expression, Node* commandThen): Node("Se") {
  this->addChild(expression);
  this->addChild(commandThen);
}

IfNode::IfNode(Node* expression, Node* commandThen, Node* commandElse): Node("Se Senao") {
  this->addChild(expression);
  this->addChild(commandThen);
  this->addChild(commandElse);
}

void IfNode::printSourceCode(const std::string& end) {
	fprintf(this->flexOut, "%s", "se (");
	this->children->at(0)->printSourceCode("");
	fprintf(this->flexOut, "%s", ") entao\n");
	this->children->at(1)->printSourceCode("");
	if (this->children->size() == 3) {
		fprintf(this->flexOut, "%s", "senao\n");
		this->children->at(2)->printSourceCode("");
	}
}
