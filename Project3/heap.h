#ifndef _heap_h
#define _heap_h 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h> // for floor command
#include "vertex.h"

// ElEMENT structure definition
struct ELEMENT {
	float key;
	int vertex;
	int pos;
};

// Heap declaration
class Heap
{	
public:
	// variables
	int capacity, size, numCalls;
	ELEMENT** H;
	Vertex** V;

	// functions
	Heap* initialize(int n);
	void printHeap(Heap* heap);
	
	// heap operations
	void insert(Heap* heap, ELEMENT* element);
	ELEMENT* extractMin(Heap* heap);
	void decreaseKey(Heap* heap, int index, float value);
	void minHeapify(Heap* heap, int index);
	void buildHeap(Heap* heap);
	void movingUp(Heap* heap, int pos);

	// heap extra functions
	int parent(int n);
	int left(int n);
	int right(int n);
	void swap(Heap* heap, int x, int y);
};
#endif
