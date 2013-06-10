#include "returnnode.h"

ReturnNode::ReturnNode(Node* expression): Node("Retorna") {
  this->addChild(expression);
}

void ReturnNode::printSourceCode() {}