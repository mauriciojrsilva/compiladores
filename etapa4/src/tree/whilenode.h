#ifndef WHILENODE_H
#define WHILENODE_H

#include "node.h"

class WhileNode : public Node {

public:
  WhileNode(Node* expression, Node* command);
  void printSourceCode();
};

#endif // WHILENODE_H
