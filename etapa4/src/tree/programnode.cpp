#include "programnode.h"

ProgramNode::ProgramNode(): Node("Programa") {}

void ProgramNode::printSourceCode() {
  for (std::list<Node*>::iterator it = this->children->begin(); it != this->children->end(); it++)
    (*it)->printSourceCode();
}
