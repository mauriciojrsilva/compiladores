#ifndef WHILENODE_H
#define WHILENODE_H

#include "node.h"

class WhileNode : public Node {

public:
  WhileNode(Node* expression, Node* command);
  void printSourceCode(const std::string& end);
};

#endif // WHILENODE_H
