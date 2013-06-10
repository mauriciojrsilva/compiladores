#include "literalnode.h"

LiteralNode::LiteralNode(const std::string& literal, const Common::DataType& dataType):
  ExpressionNode("Expressao literal", dataType), literal(literal) {}

void LiteralNode::printSourceCode() {
  // TODO
}