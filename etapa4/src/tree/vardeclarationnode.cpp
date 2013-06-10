#include "vardeclarationnode.h"
#include <iostream>

VarDeclarationNode::VarDeclarationNode(const std::string &varName, Common::DataType dataType):
  Node("Declaracao de variavel"), varName(varName), dataType(dataType) {}

void VarDeclarationNode::printSourceCode() {}