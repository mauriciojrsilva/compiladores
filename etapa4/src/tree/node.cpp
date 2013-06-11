#include "node.h"
#include <iostream>

Node::Node(): parent(NULL), flexOut(yyout) {
  this->children = new std::vector<Node*>();	
}

Node::Node(const std::string& name): name(name), parent(NULL), flexOut(yyout) {
  this->children = new std::vector<Node*>();	
}

Node::Node(const std::string& name, std::vector<Node*>* children): name(name), children(children), parent(NULL), flexOut(yyout) {
	for (std::vector<Node*>::iterator it = this->children->begin(); it != this->children->end(); it++)
		(*it)->setParent(this);
}

void Node::addChild(Node* child) {
	this->children->push_back(child);
	child->setParent(this);
}

void Node::addChildren(std::vector<Node*>* children) {
	for (std::vector<Node*>::iterator it = children->begin(); it != children->end(); it++) {
		this->children->push_back((*it));
		(*it)->setParent(this);
	}
}

Node* Node::getParent() const {
	return this->parent;
}

void Node::setParent(Node* parent) {
	this->parent = parent;
}

void Node::print(int level) {
  this->printSpaces(level);
  std::cout << this->name << "\n";
  for (std::vector<Node*>::iterator it = children->begin(); it != children->end(); it++)
    (*it)->print(level+1);
}

std::string Node::dataTypeToString(const Common::DataType& dataType) {
  switch (dataType) {
  case Common::BOOL:
    return "booleano";
  case Common::INT:
    return "inteiro";
  case Common::FLOAT:
    return "flutuante";
  case Common::CHAR:
    return "caractere";
  case Common::STRING:
    return "cadeia";
  default:
    break;
  }

  return "ERROR!";
}

void Node::printSpaces(int level) {
  for (int i = 0; i < level; i++)
    std::cout << "  ";
}
