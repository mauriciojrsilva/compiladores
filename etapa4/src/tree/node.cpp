#include "node.h"
#include <iostream>

Node::Node() {
	this->children = new std::list<Node*>();
}

Node::Node(const std::string& name): name(name) {
  this->children = new std::list<Node*>();
}

Node::Node(const std::string& name, std::list<Node*>* children): name(name), children(children) {}

void Node::addChild(Node* child) {
	this->children->push_back(child);
}

void Node::addChildren(std::list<Node*>* children) {
	this->children->insert(this->children->end(), children->begin(), children->end());
}

void Node::printSourceCode() {
  //
}

void Node::print(int level) {
  this->printSpaces(level);
  std::cout << this->name << "\n";
  for (std::list<Node*>::iterator it = children->begin(); it != children->end(); it++)
    (*it)->print(level+1);
}

void Node::printSpaces(int level) {
  for (int i = 0; i < level; i++)
    std::cout << "  ";
}
