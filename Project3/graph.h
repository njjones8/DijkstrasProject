#ifndef _graph_h
#define _graph_h 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "node.h"

class Graph
{
private:
	bool directed = false;
	Node** adjList;

public:
	Graph();
	Graph(int, int);

	void insertNode(int x, int y, int edgeWeight);
	void setDirected(bool);
};

#endif