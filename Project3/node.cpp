#include "node.h"

Node::Node()
{
	num = -1;
	weight = 0;
	next = NULL;
}

Node::Node(int d, int w)
{
	num = d;
	weight = w;
	next = NULL;
}
