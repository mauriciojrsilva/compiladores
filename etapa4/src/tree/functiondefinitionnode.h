#ifndef FUNCTIONDEFINITIONNODE_H
#define FUNCTIONDEFINITIONNODE_H

#include <string>
#include "node.h"

class FunctionDefinitionNode : public Node {

public:
  FunctionDefinitionNode();
  void printSourceCode();
};

#endif // FUNCTIONDEFINITIONNODE_H
