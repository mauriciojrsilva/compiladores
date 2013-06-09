#include "declarevarnode.h"
#include <iostream>

DeclareVarNode::DeclareVarNode(std::string varName, Common::DataType dataType):
    name("Declaracao de variavel"), varName(varName), dataType(dataType) {}

void DeclareVarNode::printSourceCode() {

}

void DeclareVarNode::print() {
    std::cout << this->name << "\n";
}
