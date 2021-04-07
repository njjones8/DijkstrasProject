#ifndef _node_h
#define _node_h 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Node
{
public:
	Node* next;
	int dest;
	float weight;
	
	// constructor 
	Node();
	Node(int, int);
};

#endif