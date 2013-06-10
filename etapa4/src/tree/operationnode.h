#ifndef OPERATIONNODE_H
#define OPERATIONNODE_H

#include "expressionnode.h"
#include "common.h"

class OperationNode : public ExpressionNode {

public:
  OperationNode(const Common::OperationType& operationType, Node* leftSide, Node* rightSide);
  void printSourceCode();

private:
  Common::OperationType operationType;
};

#endif // OPERATIONNODE_H
