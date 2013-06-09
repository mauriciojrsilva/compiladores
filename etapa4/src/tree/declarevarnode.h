#ifndef DECLAREVARNODE_H
#define DECLAREVARNODE_H

#include <string>
#include "node.h"
#include "common.h"

class DeclareVarNode : public Node {

public:
	DeclareVarNode(std::string varName, Common::DataType dataType);
	void printSourceCode();
	void print();

private:
	std::string name;
	std::string varName;
	Common::DataType dataType;
};

#endif // DECLAREVARNODE_H
