#ifndef _vertex_h
#define _vertex_h 1

class Vertex
{
private:
	int color, pi, position;
	float distance;
public:
	Vertex();
	Vertex(int, int, float, int);
};

#endif