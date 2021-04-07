#include "node.h"

Node::Node()
{
	dest = -1;
	weight = 0;
	next = NULL;
}

Node::Node(int d, int w)
{
	dest = d;
	weight = w;
	next = NULL;
}
