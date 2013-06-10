#ifndef FUNCTIONCALLNODE_H
#define FUNCTIONCALLNODE_H

#include <string>
#include <list>
#include "node.h"

class FunctionCallNode : public Node {

public:
  FunctionCallNode(const std::string& functionName, std::list<Node*>* children);
  void printSourceCode();

private:
  std::string functionName;
};

#endif // FUNCTIONCALLNODE_H
