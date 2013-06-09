#include "declarevectornode.h"
#include <iostream>

DeclareVectorNode::DeclareVectorNode(std::string vectorName, Common::DataType dataType, int size):
	name("Declaracao de vetor"), vectorName(vectorName), dataType(dataType), size(size) {}

void DeclareVectorNode::printSourceCode() {}

void DeclareVectorNode::print() {
	std::cout << this->name << "\n";
}
