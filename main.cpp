

#ifndef TREE_H_
#define TREE_H_
#include "Tree/Tree.h"
#endif

#ifndef ADDITIONAL_H
#define ADDITIONAL_H
#include "Tree/Additional.h"
#endif

#ifndef DIFFERENCIATOR_H
#define DIFFERENCIATOR_H
#include "../Differenciator/Differenciator/Differenciator.h"
#endif


int main() {
    class Differenciator differ;
    differ.LoadBase();
    differ.Differenciate();
    printf("And now...\n");
    differ.DumpString();
}