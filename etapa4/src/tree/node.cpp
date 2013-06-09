#include "node.h"

Node::Node() {
    this->children = new std::list<Node*>();
}

void Node::addChild(Node* child) {
    this->children->push_back(child);
}

void Node::printSourceCode() {
    int i = 0;
    i++;
    i++;
}

void Node::print() {
    int i = 0;
    i++;
    i++;
}