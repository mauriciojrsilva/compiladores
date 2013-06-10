#include "node.h"
#include <iostream>

Node::Node(): flexOut(yyout) {
  this->children = new std::vector<Node*>();
}

Node::Node(const std::string& name): name(name), flexOut(yyout) {
  this->children = new std::vector<Node*>();
}

Node::Node(const std::string& name, std::vector<Node*>* children): name(name), children(children), flexOut(yyout) {}

void Node::addChild(Node* child) {
	this->children->push_back(child);
}

void Node::addChildren(std::vector<Node *> *children) {
	this->children->insert(this->children->end(), children->begin(), children->end());
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