#ifndef DECLAREVECTORNODE_H
#define DECLAREVECTORNODE_H

#include <string>
#include "node.h"
#include "common.h"

class DeclareVectorNode : public Node {

public:
    DeclareVectorNode(Common::DataType dataType, int size);
    void printSourceCode();
    void print();

private:
    Common::DataType dataType;
    std::string name;
};

#endif // DECLAREVECTORNODE_H
