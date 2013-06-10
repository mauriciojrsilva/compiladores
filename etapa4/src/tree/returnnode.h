#ifndef RETURNNODE_H
#define RETURNNODE_H

#include "node.h"

class ReturnNode : public Node {

public:
  ReturnNode(Node* expression);
  void printSourceCode();
};

#endif // RETURNNODE_H
