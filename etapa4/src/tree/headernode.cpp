#include "headernode.h"
#include <stdio.h>

HeaderNode::HeaderNode(const std::string &functionName, Common::DataType dataType, std::vector<Node *> *children):
  Node("Cabecalho", children), functionName(functionName), dataType(dataType) {}

void HeaderNode::printSourceCode(const std::string& end) {
  fprintf(this->flexOut, "%s", this->functionName.c_str());
  fprintf(this->flexOut, "%s", ": ");
  fprintf(this->flexOut, "%s", this->dataTypeToString(this->dataType).c_str());
	fprintf(this->flexOut, "%s", " (");
  for (unsigned int i = 0; i < this->children->size(); i++) {
    this->children->at(i)->printSourceCode("");
    if (i != this->children->size()-1)
      fprintf(this->flexOut, "%s", ", ");
  }
  fprintf(this->flexOut, "%s", ")");
}
