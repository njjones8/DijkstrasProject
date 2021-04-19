#include "node.h"

Node::Node()
{
	num = -1;
	weight = 0;
	next = NULL;
}

Node::Node(int d)
{
	num = d;
	weight = 0;
	next = NULL;
}

Node::Node(int d, float w)
{
	num = d;
	weight = w;
	next = NULL;
}
