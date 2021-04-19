#ifndef _graph_h
#define _graph_h 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "node.h"

class Graph
{
private:
	int numVertices;
	bool directed;
	Node** adjList;

public:
	Graph();
	Graph(int, std::string);

	void insertNode(int x, int y, float edgeWeight);
	bool direction(std::string);
	void print();
	int getVertices();
	
	Node** getList();
};

#endif