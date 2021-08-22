

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

Node::Node()
{
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	status = NOSTAT;
	data = NAN;
}

Node::Node(Node* parent_, Node* left_, Node* right_, double data_, int status_)
{
	parent = parent_;
	left = left_;
	right = right_;
	status = status_;
	data = data_;
}

void Node::fprint(FILE* potok) {
	if (status == BASIC) fprintf(potok, "%.9lg", data);
	else {
		switch (status) {
		case PLUS:
			fprintf(potok, "+");
			break;
		case MINUS:
			fprintf(potok, "-");
			break;
		case MULT:
			fprintf(potok, "*");
			break;
		case DIVIDE:
			fprintf(potok, "/");
			break;
		case POW:
			fprintf(potok, "^");
			break;
		case VAR:
			fprintf(potok, "x");
			break;
		case NUL:
			fprintf(potok, "null");
			break;
		case COS:
			fprintf(potok, "cos");
			break;
		case SIN:
			fprintf(potok, "sin");
			break;
		case LOG:
			fprintf(potok, "log");
			break;
		default:
			printf("There no value ");
		}
	}
}