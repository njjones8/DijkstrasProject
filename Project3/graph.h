#ifndef _graph_h
#define _graph_h 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "node.h"

class Graph
{
private:
	bool directed;
	Node** adjList;

public:
	Graph();
	Graph(int, std::string);

	void insertNode(int x, int y, int edgeWeight);
	bool direction(std::string);
	
};

#endif