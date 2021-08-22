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
    const double e = 2.718281828459045;

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
    else if (node->status == DIVIDE) { // Очерёдность?? Нужны тесты // There mistake
        node->status = MINUS;

        Node* reduced = new Node(node, nullptr, node->right, NAN, DIVIDE);
        node->right->parent = reduced;
        Node* left_dif = CopyBranch(reduced, node->left);
        reduced->left = left_dif; 
        DifferTree(left_dif);

        Node* subtracted = new Node(node, node->left, nullptr, NAN, MULT);
        node->left->parent = subtracted;
        Node* div = new Node(subtracted, nullptr, nullptr, NAN, DIVIDE);
        subtracted->right = div;
        Node* right_div = CopyBranch(div, node->right);
        div->left = right_div;
        DifferTree(right_div);

        Node* pow = new Node(div, nullptr, nullptr, NAN, POW);
        div->right = pow;
        Node* copy_right = CopyBranch(pow, node->right);
        pow->left = copy_right;
        Node* two = new Node(pow, nullptr, nullptr, 2, BASIC); // 2 is power of g(x)
        pow->right = two;        
    
        node->left = reduced;
        node->right = subtracted;
    }
    else if (node->status == SIN) {
        node->status = COS; 
        Node* mult = new Node(node->parent, node, nullptr, NAN, MULT);
        if (node->parent == nullptr) root = mult;
        else {
            if (node->parent->left == node) node->parent->left = mult;
            else if (node->parent->right == node) node->parent->right = mult;
        }
        node->parent = mult;

        Node* differ = CopyBranch(mult, node->right);
        mult->right = differ;
        DifferTree(differ);
    }
    else if (node->status == COS) { // need test
        node->status = SIN;
        Node* mult = new Node(node->parent, nullptr, nullptr, NAN, MULT);
        Node* mult_minus = new Node(mult, node, nullptr, NAN, MULT);
        mult->left = mult_minus;
        Node* minus = new Node(mult_minus, nullptr, nullptr, -1, BASIC);
        mult_minus->right = minus;
        if (node->parent == nullptr) root = mult;
        else {
            if (node->parent->left == node) node->parent->left = mult;
            else if (node->parent->right == node) node->parent->right = mult;
        }
        node->parent = mult_minus;

        Node* differ = CopyBranch(mult, node->right);
        mult->right = differ;
        DifferTree(differ);
    }
    else if (node->status == LOG) { /// Log [f] (g),            IF F and G isn't functions??     need test
        Node* mult = new Node(node->parent, nullptr, nullptr, NAN, MULT);
        if (node->parent == nullptr) root = mult;
        else {
            if (node->parent->left == node) node->parent->left = mult;
            else if (node->parent->right == node) node->parent->right = mult;
        }
        Node* left_log = new Node(mult, nullptr, nullptr, NAN, LOG);
        mult->left = left_log;
        Node* basis = CopyBranch(left_log, node->left);
        left_log->left = basis;
        Node* e_arg = new Node(left_log, nullptr, nullptr, e, BASIC);
        left_log->right = e_arg;

        Node* minus = new Node(mult, nullptr, nullptr, NAN, MINUS);
        mult->right = minus;

        Node* left_div = new Node(minus, nullptr, nullptr, NAN, DIVIDE);
        minus->left = left_div;
        Node* one = new Node(left_div, nullptr, nullptr, 1, BASIC);
        left_div->left = one;
        Node* right_differ = CopyBranch(left_div, node->right);
        left_div->right = right_differ;
        DifferTree(right_differ);

        Node* right_div = new Node(minus, node, nullptr, NAN, DIVIDE);
        minus->right = right_div;
        node->parent = right_div;
        Node* left_differ = CopyBranch(right_div, node->left);
        right_div->right = left_differ;
        DifferTree(left_differ);
    }
    else if (node->status == POW) {
        Node* mult = new Node(node->parent, node, nullptr, NAN, MULT);
        if (node->parent == nullptr) root = mult;
        else {
            if (node->parent->left == node) node->parent->left = mult;
            else if (node->parent->right == node) node->parent->right = mult;
        }
        node->parent = mult;
        Node* plus = new Node(mult, nullptr, nullptr, NAN, PLUS);
        mult->right = plus;

        Node* left_mult = new Node(plus, nullptr, nullptr, NAN, MULT);
        plus->left = left_mult;
        Node* divide = new Node(left_mult, nullptr, nullptr, NAN, DIVIDE);
        left_mult->left = divide;
        Node* divisible = CopyBranch(divide, node->right);
        divide->left = divisible;
        Node* divisor = CopyBranch(divide, node->left);
        divide->right = divisor;
        Node* left_differ = CopyBranch(left_mult, node->left);
        left_mult->right = left_differ;
        DifferTree(left_differ);

        Node* right_mult = new Node(plus, nullptr, nullptr, NAN, MULT);
        plus->right = right_mult;
        Node* log = new Node(right_mult, nullptr, nullptr, NAN, LOG);
        right_mult->left = log;
        Node* log_base = new Node(log, nullptr, nullptr, e, BASIC);
        log->left = log_base;
        Node* log_arg = CopyBranch(log, node->left);
        log->right = log_arg;
        Node* right_differ = CopyBranch(right_mult, node->right);
        right_mult->right = right_differ;
        DifferTree(right_differ);
    }
}
