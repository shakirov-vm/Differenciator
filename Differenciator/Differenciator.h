



#ifndef TREE_H_
#define TREE_H_
#include "Tree/Tree.h"
#endif

class Differenciator : public Tree {
    //our_hash_table* states;
public:
    Differenciator();
    void DumpString();
    void Differenciate();

    void DifferTree(class Node* node);
};

void PrintExpression(class Node* node, FILE* potok);