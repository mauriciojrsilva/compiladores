#include "returnnode.h"
#include <stdio.h>

ReturnNode::ReturnNode(Node* expression): Node("Retorna") {
  this->addChild(expression);
}

void ReturnNode::printSourceCode(const std::string& end) {
	fprintf(this->flexOut, "%s", "retorna ");
	this->children->at(0)->printSourceCode("");
	fprintf(this->flexOut, "%s", ";\n");
}
