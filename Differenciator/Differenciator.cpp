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

Differenciator::Differenciator() {
}


void Differenciator::DumpString() {
    PrintExpression(root, stdout);
    printf("\n");
}

void PrintExpression(class Node* node, FILE* potok) {
    if (node != nullptr)
    {
        //printf("%lf - %d\n", node->data, node->status);
        if(node->left != nullptr) printf("(");
        PrintExpression(node->left, potok);
        if (node->status != NUL) {
            node->fprint(potok);
        }
        PrintExpression(node->right, potok);
        if(node->left != nullptr) printf(")");
    }
}

void Differenciator::Differenciate() {
    DifferTree(root);
}

void Differenciator::DifferTree(class Node* node) { // if root no actual after change?
    if (node->status == VAR) {
        node->status = BASIC;
        node->data = 1;
    }
    else if (node->status == PLUS || node->status == MINUS) { 
        DifferTree(node->left);
        DifferTree(node->right);
    }
    else if (node->status == BASIC) {
        node->data = 0;
    }
    else if (node->status == MULT) { 
        printf("We enter\n");
        Node* left_mult = new Node(node, node->left, nullptr, (double)NAN, MULT);
        Node* right_mult = new Node(node, nullptr, node->right, (double)NAN, MULT);
        node->status = PLUS;
        printf("We do mult\n");

        node->left->parent = left_mult;
        Node* left_dif = CopyBranch(left_mult, node->left);
        left_mult->right = left_dif;
        DifferTree(left_dif);
        printf("We do left\n");

        node->right->parent = right_mult;
        Node* right_dif = CopyBranch(right_mult, node->right);
        right_mult->left = right_dif;
        DifferTree(right_dif);
        printf("We do right\n");

        node->left = left_mult;
        node->right = right_mult;
    }
    else if (node->status == COS) {
        node->status = SIN; 
        Node* mult = new Node(node->parent, node, nullptr, NAN, MULT);
        if (node->parent == nullptr) root = mult;
        node->parent = mult;

        Node* differ = CopyBranch(mult, node->right);
        mult->right = differ;
        DifferTree(differ);
    }
}
