#ifndef DECLAREVARNODE_H
#define DECLAREVARNODE_H

#include <string>
#include "node.h"
#include "common.h"

class DeclareVarNode : public Node {

public:
    DeclareVarNode(Common::DataType dataType);
    void printSourceCode();
    void print();

private:
    Common::DataType dataType;
    std::string name;
};

#endif // DECLAREVARNODE_H
