#include <iostream>
#include <string.h>

#ifndef TREE_H_
#define TREE_H_
#include "../Tree/Tree.h"
#endif

#ifndef DIFFERENCIATOR_H
#define DIFFERENCIATOR_H
#include "Differenciator.h"
#endif

void Differenciator::DumpString() {
    PrintExpression(root, stdout);
    printf("\n");
}
// STRCMP OR STRNCMP
void PrintExpression(class Node* node, FILE* potok) {
    if (node != nullptr)
    {
        //if(node->left != nullptr) printf("(");
        PrintExpression(node->left, potok);
        if (strcmp(node->data, "null")) printf(" %s ", node->data);
        PrintExpression(node->right, potok);
        //if(node->left != nullptr) printf(")");
    }
}

void Differenciator::Differenciate() {
    DifferTree(root);
}

void DifferTree(class Node* node) {
    if (!strcmp(node->data, "x")) {
        printf("x? - %s\n", node->data);
        sprintf(node->data, "1");
    }
    else if (!strcmp(node->data, "+")) {
        printf("+? - %s\n", node->data);
        DifferTree(node->left);
        DifferTree(node->right);
    }
    else if (!atof(node->data)) {  // BAD!
        printf("num? - %s\n", node->data);
        sprintf(node->data, "0");
    }
    else if (!strcmp(node->data, "*")) { // need test
        printf("*? - %s\n", node->data);
        char* mult = new char[1];
        sprintf(mult, "*");

        Node* left_mult = new Node(node, node->left, nullptr, mult);
        Node* right_mult = new Node(node, nullptr, node->right, mult);
        node->left = left_mult;
        node->right = right_mult;
        sprintf(node->data, "+");

        Node* left_dif = new Node(node, node->left, nullptr, mult);
        left_mult->left = node->left;
        node->left->parent = left_mult;
        left_mult->parent = node;
        left_dif = CopyBranch(left_mult, node->left);
        DifferTree(left_dif);

        Node* right_dif = new Node(node, nullptr, node->right, mult);
        right_mult->right = node->right;
        node->right->parent = left_mult;
        right_mult->parent = node;
        right_dif = CopyBranch(right_mult, node->right);
        DifferTree(right_dif);

        node->left = left_mult;
        node->right = right_mult;

        delete[] mult;
        //Вот тут скопировать обе ветки (левую и правую), в потом их дифференцировать
        //Node* left_dif = new Node();
        //class Node* right_dif = (class Node*)calloc(1, sizeof(class Node));

        //left_mult = ChargeNode(node->left, "*", node)
    }
}
