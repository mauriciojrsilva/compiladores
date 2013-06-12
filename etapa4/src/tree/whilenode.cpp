#include "whilenode.h"
#include <stdio.h>

WhileNode::WhileNode(Node *expression, Node *command): Node("Enquanto") {
  this->addChild(expression);
  this->addChild(command);
}

void WhileNode::printSourceCode(const std::string& end) {
	fprintf(this->flexOut, "%s", "enquanto (");
	this->children->at(0)->printSourceCode("");
	fprintf(this->flexOut, "%s", ")\n");
	this->children->at(1)->printSourceCode(";\n");
}
