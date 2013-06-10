#ifndef NODE_H
#define NODE_H

#include <list>
#include <string>
//#include "symbol.h"

class Node {

public:
	Node();
  Node(const std::string& name);
  Node(const std::string& name, std::list<Node*>* children);
	void addChild(Node* child);
	void addChildren(std::list<Node*>* children);
  void print(int level);
  virtual void printSourceCode() = 0; //Temporarily this method won't be pure virtual, to allow the creation of instances of this class

protected:
  void printSpaces(int level);
  std::string name;

private:
	std::list<Node*>* children;
	//Symbol* symbol;
};

#endif // NODE_H
