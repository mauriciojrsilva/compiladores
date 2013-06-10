#ifndef ASSIGNMENTNODE_H
#define ASSIGNMENTNODE_H

#include <string>
#include "node.h"

class AssignmentNode : public Node {

public:
  AssignmentNode(const std::string& varName, Node* expressionAssigned);
  AssignmentNode(const std::string& varName, Node* expressionIndex, Node* expressionAssigned);
  void printSourceCode();

private:
  std::string varName;
};

#endif // ASSIGNMENTNODE_H
