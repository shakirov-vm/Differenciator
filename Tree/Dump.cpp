#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

void Tree::DumpGraph()
{
	FILE* potok = FileOpen("Enter file name, where will be dump graph\n", "w");
	if (potok == nullptr) return;

	fprintf(potok, "digraph G {\n");
	PrintGraph(root, potok, 1);

	fprintf(potok, "}\n");

	fclose(potok);
}

void PrintGraph(Node* node, FILE* potok, size_t i) // So slooow
{
	if (node->left != nullptr)
	{
		fprintf(potok, "\"%d: ", i);
		node->fprint(potok);
		fprintf(potok, "\" -> \"%d: ", i + 1);
		node->left->fprint(potok);
		fprintf(potok, "\";\n");

		fprintf(potok, "\"%d: ", i);
		node->fprint(potok);
		fprintf(potok, "\" -> \"%d: ", i * 32);
		node->right->fprint(potok);
		fprintf(potok, "\";\n");

		PrintGraph(node->left, potok, i * 2);
		PrintGraph(node->right, potok, i + 1);
	}
}

void Tree::DumpBase()  //          DO text for writing
{
	FILE* potok = FileOpen("Enter file name, where will be dump base\n", "w");
	if (potok == nullptr) return;

	int depth = 0;
	PrintBase(root, potok, &depth, 0);
	fprintf(potok, "}\n");
	fclose(potok);
}

void PrintBase(Node* node, FILE* potok, int* depth, int equalizer) //The value of the equalizer is selected so that there are no extra brackets
{
	if (node != nullptr)
	{
		if (!equalizer) {
			for (int j = 0; j < *depth; j++) fprintf(potok, "\t");
			fprintf(potok, "{\n");
			++(*depth);
			++(*depth);
		}
		for (int j = 0; j < (*depth) - 1; j++) fprintf(potok, "\t");
		fprintf(potok, "$");
		node->fprint(potok);
		fprintf(potok, "$\n");
		PrintBase(node->left, potok, depth, 0);
		PrintBase(node->right, potok, depth, 1);
		if (equalizer) {
			--(*depth);
			--(*depth);
			for (int j = 0; j < *depth; j++) fprintf(potok, "\t");
			fprintf(potok, "}\n");
		}
	}
}

FILE* FileOpen(const char* text, const char* mode) {
	printf(text);
	char* answer = (char*)calloc(MAX_NAME_SIZE, sizeof(char));

	fseek(stdin, 0, SEEK_END);
	std::cin.getline(answer, MAX_NAME_SIZE, '\n');

	FILE* potok = fopen(answer, mode);
	free(answer);
	return potok;
}