
#define MAX_DATA_SIZE 100
#define MAX_BASE_SIZE 100000
#define MAX_NAME_SIZE 75

#include <iostream>
#include <unordered_map>

class MyEqualTo {
public:
	bool operator() (const char* str1, const char* str2) const {
		return !strcmp(str1, str2);
	}
};


typedef std::unordered_map<const char*, size_t, std::hash<const char*>> our_hash_table;  // PTR Equal?

enum STATUS {
	NOSTAT = 1001,
	BASIC  = 0,
	PLUS   = 1,
	MINUS  = 2,
	MULT   = 3,
	DIVIDE = 4,
	POW    = 5, 
	VAR    = 100,
	NUL    = 101,
	COS    = 11,
	SIN    = 12,
	LOG    = 13,
};

class Node {
public:
	Node* parent;
	Node* left;
	Node* right;
	double data;
	size_t status;

	Node();
	Node(Node* parent_, Node* left_, Node* right_, double data_, int status_);
	void fprint(FILE* potok);
};

class Tree
{
protected:
	class Node* root;

public:
	Tree();
	~Tree();
	Tree& operator= (const Tree& node) = delete;
	Tree(const Tree&) = delete;

	void LoadBase();
	void DumpBase();
	void DumpGraph();
};

void DeleteBranch(Node* node);
Node* CopyBranch(Node* parent, Node* old);

void PrintBase(Node* node, FILE* potok, int* depth, int equalizer);
void PrintGraph(Node* node, FILE* potok, size_t i);

FILE* FileOpen(const char* text, const char* mode);

size_t GetStatus(char* data, our_hash_table* functions);