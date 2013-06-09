#include "headernode.h"
#include <iostream>

HeaderNode::HeaderNode(std::string functionName, Common::DataType dataType, std::list<Node *> *children):
    name("Cabeçalho"), functionName(functionName), dataType(dataType) {
    this->children = children;
}


void HeaderNode::printSourceCode() {

}

void HeaderNode::print() {
    std::cout << this->name << "\n";
}