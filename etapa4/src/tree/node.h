#ifndef NODE_H
#define NODE_H

#include <list>
#include <string>
//#include "symbol.h"

class Node {

public:
    Node();
    void addChild(Node* child);
    virtual void printSourceCode(); // = 0; Temporarily these methods won't be pure virtual, to allow the creation of instances of this class
    virtual void print(); // = 0;

protected:
    std::list<Node*> children;
    //Symbol* symbol;
};

#endif // NODE_H