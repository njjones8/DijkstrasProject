#ifndef _graph_h
#define _graph_h 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct Vertex
{
	int color;
	int weight;
	Vertex* next;
};

class Graph
{
private:
	bool directed = false;
	Vertex* adjList[];

public:
	Graph* initialize(int n, int m);
	void addNode(int x, int y, int edgeWeight);
};

#endif