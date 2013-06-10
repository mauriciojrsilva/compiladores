#ifndef VARDECLARATIONNODE_H
#define VARDECLARATIONNODE_H

#include <string>
#include "node.h"
#include "common.h"

class VarDeclarationNode : public Node {

public:
  VarDeclarationNode(const std::string& varName, Common::DataType dataType);
  void printSourceCode();

private:
	std::string varName;
	Common::DataType dataType;
};

#endif // VARDECLARATIONNODE_H
