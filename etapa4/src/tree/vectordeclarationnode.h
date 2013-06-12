#ifndef VECTORDECLARATIONNODE_H
#define VECTORDECLARATIONNODE_H

#include <string>
#include "node.h"
#include "common.h"

class VectorDeclarationNode : public Node {

public:
  VectorDeclarationNode(const std::string& vectorName, Common::DataType dataType, int size);
  void printSourceCode(const std::string& end);

private:
	std::string vectorName;
	Common::DataType dataType;
	int size;
};

#endif // VECTORDECLARATIONNODE_H
