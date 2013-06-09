#ifndef DECLAREVECTORNODE_H
#define DECLAREVECTORNODE_H

#include <string>
#include "node.h"
#include "common.h"

class DeclareVectorNode : public Node {

public:
	DeclareVectorNode(std::string vectorName, Common::DataType dataType, int size);
	void printSourceCode();
	void print();

private:
	std::string name;
	std::string vectorName;
	Common::DataType dataType;
	int size;
};

#endif // DECLAREVECTORNODE_H
