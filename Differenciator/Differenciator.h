



#ifndef TREE_H_
#define TREE_H_
#include "Tree/Tree.h"
#endif

class Differenciator : public Tree {
public:
    void DumpString();
    void Differenciate();

};

void PrintExpression(class Node* node, FILE* potok);
void DifferTree(class Node* node);