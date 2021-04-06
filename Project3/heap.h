#ifndef _heap_h
#define _heap_h 1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h> // for floor command

// ElEMENT structure definition
struct ELEMENT {
	int key;
};

// Heap declaration
class Heap
{	
public:
	// variables
	int capacity, size, numCalls;
	ELEMENT** H;

	// functions
	Heap* initialize(int n);
	void printHeap(Heap* heap);
	
	// heap operations
	void insert(Heap* heap, ELEMENT* element);
	ELEMENT* extractMin(Heap* heap);
	void decreaseKey(Heap* heap, int index, int value);
	void minHeapify(Heap* heap, int index);
	void buildHeap(Heap* heap);

	// heap extra functions
	int parent(int n);
	int left(int n);
	int right(int n);
	void swap(Heap* heap, int x, int y);
};
#endif
