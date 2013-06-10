#ifndef HEADERNODE_H
#define HEADERNODE_H

#include <string>
#include "node.h"
#include "common.h"

class HeaderNode : public Node {
public:
  HeaderNode(const std::string& functionName, Common::DataType dataType, std::list<Node*>* children);
  void printSourceCode();

private:
	std::string functionName;
	Common::DataType dataType;
};

#endif // HEADERNODE_H
