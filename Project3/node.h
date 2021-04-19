#ifndef _node_h
#define _node_h 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Node
{
public:
	Node* next;
	int num;
	float weight;
	
	// constructor 
	Node();
	Node(int);
	Node(int, float);
};

#endif