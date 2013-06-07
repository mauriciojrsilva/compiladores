#include "programnode.h"
#include <iostream>

ProgramNode::ProgramNode(): name("Programa") {}

void ProgramNode::printSourceCode() {

}

void ProgramNode::print() {
    std::cout << this->name << "\n";
    for (std::list<Node*>::iterator it = children.begin(); it != children.end(); it++)
        (*it)->print();
}
