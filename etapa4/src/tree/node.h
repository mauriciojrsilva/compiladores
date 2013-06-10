#ifndef NODE_H
#define NODE_H

#include <list>
#include <string>
#include "common.h"
//#include "symbol.h"
extern FILE* yyout;

class Node {

public:
	Node();
  Node(const std::string& name);
  Node(const std::string& name, std::list<Node*>* children);
	void addChild(Node* child);
	void addChildren(std::list<Node*>* children);
  void print(int level);
  virtual void printSourceCode() = 0;

protected:  
  std::string dataTypeToString(const Common::DataType& dataType);
  std::string name;
	std::list<Node*>* children;
  FILE* flexOut;
	//Symbol* symbol;

private:
  void printSpaces(int level);
};

#endif // NODE_H
