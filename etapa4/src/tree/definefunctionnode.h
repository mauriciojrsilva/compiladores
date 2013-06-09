#ifndef DEFINEFUNCTIONNODE_H
#define DEFINEFUNCTIONNODE_H

#include <string>
#include "node.h"

class DefineFunctionNode : public Node {

public:
	DefineFunctionNode();
	void printSourceCode();
	void print();

private:
	std::string name;
};

#endif // DEFINEFUNCTIONNODE_H
