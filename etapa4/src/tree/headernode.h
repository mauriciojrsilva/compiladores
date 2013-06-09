#ifndef HEADERNODE_H
#define HEADERNODE_H

#include <string>
#include "node.h"
#include "common.h"

class HeaderNode : public Node {
public:
	HeaderNode(std::string functionName, Common::DataType dataType, std::list<Node*>* children);
	void printSourceCode();
	void print();

private:
	std::string name;
	std::string functionName;
	Common::DataType dataType;
};

#endif // HEADERNODE_H
