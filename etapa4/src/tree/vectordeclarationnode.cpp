#include "vectordeclarationnode.h"

VectorDeclarationNode::VectorDeclarationNode(const std::string &vectorName, Common::DataType dataType, int size):
  Node("Declaracao de vetor"), vectorName(vectorName), dataType(dataType), size(size) {}

void VectorDeclarationNode::printSourceCode() {}