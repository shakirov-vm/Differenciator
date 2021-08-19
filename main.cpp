

#ifndef TREE_H_
#define TREE_H_
#include "Tree/Tree.h"
#endif

#ifndef DIFFERENCIATOR_H
#define DIFFERENCIATOR_H
#include "../Differenciator/Differenciator/Differenciator.h"
#endif

// memory allocate error
// File* error

int main() {
    class Differenciator differ;
    differ.LoadBase();
    differ.Differenciate();
    printf("And now...\n");
    differ.DumpString();
   // differ.DumpGraph();
    differ.DumpBase();
}