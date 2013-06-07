#include "declarevectornode.h"
#include <iostream>

DeclareVectorNode::DeclareVectorNode(Common::DataType dataType, int size): dataType(dataType), name("Declaracao de vetor") {}

void DeclareVectorNode::printSourceCode() {

}

void DeclareVectorNode::print() {
    std::cout << this->name << "\n";
}
