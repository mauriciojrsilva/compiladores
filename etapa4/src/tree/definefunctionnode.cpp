#include "definefunctionnode.h"
#include <iostream>

DefineFunctionNode::DefineFunctionNode() : name("Funcao") {}

void DefineFunctionNode::printSourceCode() {
	// TODO
}

void DefineFunctionNode::print() {
	std::cout << this->name << "\n";
	for (std::list<Node*>::iterator it = children->begin(); it != children->end(); it++)
		(*it)->print();
}
