#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

#ifndef ADDITIONAL_H
#define ADDITIONAL_H
#include "Additional.h"
#endif

void* calloc_error(size_t elements, size_t size) {
	void* ptr = calloc(elements, size);
	if (ptr == nullptr) {
		printf("Can't allocate memory\n");
		return nullptr;
	}
	return ptr;
}

char* tolower_str(char* string)
{
	size_t len = strlen(string);
	for (size_t i = 0; i < len; i++) string[i] = tolower(string[i]);
	return string;
}

bool check_answer(char* answer, const char* right) {
	if (!strncmp(tolower_str(answer), right, strlen(right))) return true;
	if (!strncmp(tolower_str(answer), right, 1)) return true;
	return false;
}

FILE* fopen_error(char* base_name, const char* mode) {
	FILE* potok = fopen(base_name, mode);
	if (potok == nullptr) {
		printf("This file can't be open\n");
		return nullptr;
	}
	return potok;
}

FILE* file_open(const char* text, const char* mode) {
	printf(text);
	char* answer = (char*)calloc_error(MAX_NAME_SIZE, sizeof(char));

	fseek(stdin, 0, SEEK_END);
	std::cin.getline(answer, MAX_NAME_SIZE, '\n');

	FILE* potok = fopen_error(answer, mode);
	free(answer);
	return potok;
}