#ifndef HEADERNODE_H
#define HEADERNODE_H

#include <string>
#include <vector>
#include "node.h"
#include "common.h"

class HeaderNode : public Node {
public:
  HeaderNode(const std::string& functionName, Common::DataType dataType, std::vector<Node*>* children);
  void printSourceCode(const std::string& end);

private:
	std::string functionName;
	Common::DataType dataType;
};

#endif // HEADERNODE_H
