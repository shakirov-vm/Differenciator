

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

Node::Node()
{
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	status = BASIC;
	data = new char[MAX_BASE_SIZE];
	for (size_t i = 0; i < MAX_BASE_SIZE; i++) data[i] = 0;
}

Node::Node(const Node& node) {
	parent = node.parent;
	left = node.left;
	right = node.right;
	data = new char[MAX_BASE_SIZE];
	size_t len = strlen(node.data);
	size_t i = 0;
	for (; i < len; i++) {
		data[i] = node.data[i];
	}
	for (; i < MAX_BASE_SIZE; i++) {
		data[i] = node.data[i];
	}
}

Node& Node::operator= (const Node& node) {
	if (this == &node) return *this;

	parent = node.parent;
	left = node.left;
	right = node.right;
	//data = new char[MAX_BASE_SIZE];  Memory must be allocate there
	size_t len = strlen(node.data);
	size_t i = 0;
	for (; i < len; i++) {
		data[i] = node.data[i];
	}
	for (; i < MAX_BASE_SIZE; i++) {
		data[i] = node.data[i];
	}

	return *this;
}

Node::Node(Node* parent_, Node* left_, Node* right_, char* data_)
{
	parent = parent_;
	left = left_;
	right = right_;
	data = new char[MAX_BASE_SIZE];
	size_t len = strlen(data_);
	size_t i = 0;
	for (; i < len; i++) {
		data[i] = data_[i];
	}
	for (; i < MAX_BASE_SIZE; i++) {
		data[i] = data_[i];
	}
}

Node::~Node() {
	printf("KILL! ");
	delete data;
}