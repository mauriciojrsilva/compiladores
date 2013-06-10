#include "literalnode.h"
#include <stdio.h>

LiteralNode::LiteralNode(const std::string& literal, const Common::DataType& dataType):
  ExpressionNode("Expressao literal", dataType), literal(literal) {}

void LiteralNode::printSourceCode(const std::string& end) {
  fprintf(this->flexOut, "%s", literal.c_str());
}