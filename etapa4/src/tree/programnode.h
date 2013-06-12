#ifndef PROGRAMNODE_H
#define PROGRAMNODE_H

#include <string>
#include "node.h"


class ProgramNode : public Node {

public:
	ProgramNode();
  void printSourceCode(const std::string& end);
};

#endif // PROGRAMNODE_H
