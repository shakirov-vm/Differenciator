#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <iostream>
#include <unordered_map>
#include <iterator>

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

Tree::Tree()
{
	root = new Node();
}
Tree::~Tree()
{
	DeleteBranch(root);
}

void Tree::LoadBase()
{

	our_hash_table functions;
	functions.insert(std::make_pair("+", PLUS));
	functions.insert(std::make_pair("-", MINUS));
	functions.insert(std::make_pair("*", MULT));
	functions.insert(std::make_pair("/", DIVIDE));
	functions.insert(std::make_pair("^", POW));
	functions.insert(std::make_pair("x", VAR));
	functions.insert(std::make_pair("null", NUL));
	functions.insert(std::make_pair("cos", COS));
	functions.insert(std::make_pair("sin", SIN));
	functions.insert(std::make_pair("log", LOG));


	/*our_hash_table::iterator it = functions.begin();
	while (it != functions.end()) {
		printf("[%s] - [%d]\n", it->first, it->second);
		it++;
	}*/

	//printf("%d - %s\n", functions.find("+")->second, functions.find("+")->first);

	printf("You need load base. Enter name\n");
	char* base_name = (char*)calloc(100, sizeof(char));

	fseek(stdin, 0, SEEK_END);
	std::cin.getline(base_name, MAX_NAME_SIZE, '\n');

	FILE* potok = fopen(base_name, "r");
	if (potok == nullptr) return;

	struct stat buff;
	stat(base_name, &buff);
	size_t base_size = buff.st_size;

	free(base_name);

	char* base = (char*)calloc(base_size, sizeof(char));

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

		node->status = GetStatus(counter, &functions);
		if (node->status == BASIC) node->data = atoi(counter);

		counter = counter + strlen(counter) + 1;
	}

	for (; counter != end; counter++)
	{
		if (*counter == '{')
		{
			counter++;
			while (isspace(*counter)) counter++;
			counter = strtok(counter, "$");

			node = new Node(node, nullptr, nullptr, (double)NAN, NOSTAT);
			node->status = GetStatus(counter, &functions);
			if (node->status == BASIC) node->data = atoi(counter);

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

			node = new Node(node, nullptr, nullptr, (double)NAN, NOSTAT);
			node->status = GetStatus(counter, &functions);
			if (node->status == BASIC) node->data = atoi(counter);

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
	root->status = node->status;

	free(base);
}

size_t GetStatus(char* data, our_hash_table* functions) { // Is it work right?

	our_hash_table::iterator it = functions->begin();
	while (it != functions->end()) {
		if (!strcmp(it->first, data)) break;
		it++;
	}
	if (it == functions->end()) {
		printf("Don't find {%s}\n", data);
		return BASIC;
	}
	else {
		printf("from my find: {%s} - {%d}\n", it->first, it->second);
		return it->second;
	}

	/*if (functions->find(data) == functions->end()) {
		printf("\nIn status: {%s}\n", data);
		//printf("In basic variant\n");
		return BASIC;
	}
	else {
		printf("in function at: %ld\n", functions->at(data));
		return functions->at(data);
	}*/
}



Node* CopyBranch(Node* parent, Node* old) {
	//printf("Copy - %d", old->status);
	if (old != nullptr) {
		Node* node = new Node(parent, nullptr, nullptr, old->data, old->status);

		node->parent = parent;
		node->left = CopyBranch(node, old->left);
		node->right = CopyBranch(node, old->right);

		return node;
	}
	return nullptr;
}

void DeleteBranch(Node* node)
{
	printf("Branch! ");
	if (node != nullptr) {

		DeleteBranch(node->left);
		DeleteBranch(node->right);

		delete node;
	}
}