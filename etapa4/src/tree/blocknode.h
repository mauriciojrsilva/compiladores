#ifndef BLOCONODE_H
#define BLOCONODE_H

#include <list>
#include "node.h"

class BlockNode : public Node {

public:
  BlockNode(std::list<Node*>* children);
  void printSourceCode();
};

#endif // BLOCONODE_H
