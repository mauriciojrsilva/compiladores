#ifndef OUTPUTNODE_H
#define OUTPUTNODE_H

#include <list>
#include "node.h"

class OutputNode : public Node {

public:
  OutputNode(std::list<Node*>* children);
  void printSourceCode();
};

#endif // OUTPUTNODE_H
