#include "declarevarnode.h"
#include <iostream>

DeclareVarNode::DeclareVarNode(Common::DataType dataType): dataType(dataType), name("Declaracao de variavel") {}

void DeclareVarNode::printSourceCode() {

}

void DeclareVarNode::print() {
    std::cout << this->name << "\n";
}
