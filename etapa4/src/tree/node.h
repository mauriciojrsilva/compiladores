#ifndef NODE_H
#define NODE_H

#include <list>
//#include "symbol.h"


class Node {

public:
    Node();
    void addChild(Node* child);
    virtual void printSourceCode();
    virtual void print();

private:
    //virtual void abstractMethod() = 0;
    std::list<Node*> children;
    //Symbol* symbol;
};

#endif // NODE_H