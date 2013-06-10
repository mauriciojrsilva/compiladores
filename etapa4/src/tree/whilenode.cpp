#include "whilenode.h"

WhileNode::WhileNode(Node *expression, Node *command): Node("Enquanto") {
  this->addChild(expression);
  this->addChild(command);
}

void WhileNode::printSourceCode() {}