#include <cstddef>
#include <cstdio>

void* calloc_error(size_t elements, size_t size);
bool check_answer(char* answer, const char* right);
FILE* fopen_error(char* base_name, const char* mode);
FILE* file_open(const char* text, const char* mode);