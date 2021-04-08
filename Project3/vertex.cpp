#include "vertex.h"


Vertex::Vertex()
{
	color = 0;
	pi = 0;
	distance = 0;
	position = 0;
}

Vertex::Vertex(int c, int p, float d, int pos)
{
	color = c;
	pi = p;
	distance = d;
	position = pos;
}