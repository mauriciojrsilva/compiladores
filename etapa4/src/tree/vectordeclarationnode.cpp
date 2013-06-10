#include "vectordeclarationnode.h"
#include <stdio.h>
#include <sstream>

VectorDeclarationNode::VectorDeclarationNode(const std::string &vectorName, Common::DataType dataType, int size):
  Node("Declaracao de vetor"), vectorName(vectorName), dataType(dataType), size(size) {}

void VectorDeclarationNode::printSourceCode() {
  std::stringstream sizeStr;
  sizeStr << this->size;

  fprintf(this->flexOut, "%s", this->vectorName.c_str());
  fprintf(this->flexOut, "%s", ": ");
  fprintf(this->flexOut, "%s", this->dataTypeToString(this->dataType).c_str());
  fprintf(this->flexOut, "%s", "[");
  fprintf(this->flexOut, "%s", sizeStr.str().c_str());
  fprintf(this->flexOut, "%s", "]");
  fprintf(this->flexOut, "%s", ";\n");
}