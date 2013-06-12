#ifndef BLOCONODE_H
#define BLOCONODE_H

#include <vector>
#include "node.h"

class BlockNode : public Node {

public:
  BlockNode(std::vector<Node*>* children);
  void printSourceCode(const std::string& end);
};

#endif // BLOCONODE_H
