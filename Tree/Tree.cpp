#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <iostream>

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

#ifndef ADDITIONAL_H
#define ADDITIONAL_H
#include "Additional.h"
#endif

Tree::Tree()
{
	root = new Node();
}
Tree::~Tree()
{
	DeleteBranch(root);
}

Node::Node()
{
	parent = nullptr;
	left = nullptr;
	right = nullptr;
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
	data = new char[MAX_BASE_SIZE];
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

void Tree::LoadBase()
{
	printf("You need load base. Enter name\n");
	char* base_name = (char*)calloc_error(100, sizeof(char));

	fseek(stdin, 0, SEEK_END);
	std::cin.getline(base_name, MAX_NAME_SIZE, '\n');

	FILE* potok = fopen_error(base_name, "r");
	if (potok == nullptr) return;

	struct stat buff;
	stat(base_name, &buff);
	size_t base_size = buff.st_size;

	free(base_name);

	char* base = (char*)calloc_error(base_size, sizeof(char));

	fread(base, sizeof(char), base_size, potok);

	char* end = base + base_size;

	fclose(potok);

	Node* node = new Node();
	if (node == nullptr) return;

	char* counter = base;
	// Load root
	while (isspace(*counter)) counter++;
	if (*counter == '{') {
		counter++;
		while (isspace(*counter)) counter++;
		counter = strtok(counter, "$");

		size_t len = strlen(counter);
		for (size_t i = 0; i < len; i++) {
			node->data[i] = counter[i];
		}
		counter = counter + strlen(counter) + 1;
	}

	for (; counter != end; counter++)
	{
		if (*counter == '{')
		{
			counter++;
			while (isspace(*counter)) counter++;
			counter = strtok(counter, "$");

			node = new Node(node, nullptr, nullptr, counter);
			node->parent->left = node;

			counter = counter + strlen(counter) + 1;
			continue;
		}
		if (*counter == '$')
		{
			counter++;
			while (isspace(*counter)) counter++;
			counter = strtok(counter, "$");

			node->parent->left = node;
			node = node->parent;

			node = new Node(node, nullptr, nullptr, counter);
			node->parent->right = node;

			counter = counter + strlen(counter) + 1;
			continue;
		}
		if (*counter == '}')
		{
			if (node->parent != nullptr)
			{
				node->parent->right = node;
				node = node->parent;
			}
			continue;
		}
	}
	root->left = node->left;
	root->right = node->right;
	root->data = node->data;

	free(base);
}

Node* CopyBranch(Node* parent, Node* old) {  // Very bad
	if (old != nullptr) {
		Node* node = new Node(parent, nullptr, nullptr, old->data);

		node->parent = parent;
		node->left = CopyBranch(node, old->left);
		node->right = CopyBranch(node, old->right);

		return node;
		//Node new_node = *node;          There very beeg mistake
	}
	return nullptr;
}

void DeleteBranch(Node* node)
{
	printf("Branch! ");
	if (node != nullptr) {

		DeleteBranch(node->left);
		DeleteBranch(node->right);

		//delete node->data;
		delete node;
	}
}