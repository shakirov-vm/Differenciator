
#define MAX_DATA_SIZE 100
#define MAX_BASE_SIZE 100000
#define MAX_NAME_SIZE 75

#include <iostream>

class Node {
public:
	Node* parent;
	Node* left;
	Node* right;
	char* data;

	Node();
	~Node();
	Node& operator= (const Node& node);
	Node(const Node& node);
	Node(Node* parent_, Node* left_, Node* right_, char* data_);
};

class Tree
{
public:
	//protected:
	class Node* root;
	void Play();

public:
	Tree();
	~Tree();
	Tree& operator= (const Tree& node) = delete;
	Tree(const Tree&) = delete;

	void LoadBase();
	void Game();
	void DumpBase();
	void DumpGraph();
};

void DeleteBranch(Node* node);
Node* CopyBranch(Node* parent, Node* old);
void PrintGraph(Node* node, FILE* potok, size_t i);