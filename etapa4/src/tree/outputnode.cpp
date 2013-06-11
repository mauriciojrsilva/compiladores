#include "outputnode.h"
#include <stdio.h>

OutputNode::OutputNode(std::vector<Node*>* children): Node("Saida", children) {}

void OutputNode::printSourceCode(const std::string& end) {
	fprintf(this->flexOut, "%s", "saida ");
	for (std::vector<Node*>::iterator it = this->children->begin(); it != this->children->end(); it++)
		(*it)->printSourceCode(",");
	fprintf(this->flexOut, "%s", ";\n");
}
