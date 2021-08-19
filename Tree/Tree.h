
#define MAX_DATA_SIZE 100
#define MAX_BASE_SIZE 100000
#define MAX_NAME_SIZE 75

#include <iostream>

enum STATUS {
	BASIC    = 0,
	FUNCTION = 1,
	VARIABLE = 2,
	NOVALUE  = 3
};

enum ACTIONS {
	PLUS   = 1,
	MINUS  = 2,
	MULT   = 3,
	DIVIDE = 4,
	POW    = 5
};

class Node {
public:
	Node* parent;
	Node* left;
	Node* right;
	char* data;
	int status;

	Node();
	~Node();
	Node& operator= (const Node& node);
	Node(const Node& node);
	Node(Node* parent_, Node* left_, Node* right_, char* data_);
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
FILE* file_open(const char* text, const char* mode);