#include "heap.h"


// initialize function of heap class, used to 
// allocate 
Heap *Heap::initialize(int n)
{
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	heap->numCalls = 0;
	heap->size = 0;
	heap->capacity = n;
	heap->H = (ELEMENT**)malloc(sizeof(ELEMENT*) * (n + 1));
	heap->V = (Vertex**)malloc(sizeof(Vertex*) * (n + 1));
	return heap;
}

// prints out the heap until it reaches the last element.
// the last element is then printed manually so it doesn't have a comma after it
void Heap::printHeap(Heap* heap)
{
	std::cout << "capacity=" << capacity << ", size=" << size << std::endl;
	for (int i = 1; i < heap->size; i++)
		std::cout << heap->H[i]->key << ", ";
	if (heap->size > 0)
		std::cout << heap->H[heap->size]->key << std::endl;
}

// increments heap size, places new element at last spot in heap and then
// swaps nodes up the heap until it is in the right spot
void Heap::insert(Heap* heap, ELEMENT* element)
{
	heap->size++;
	heap->H[size] = element;
	int j = size;

	while ((j > 1) && (heap->H[j]->key < heap->H[heap->parent(j)]->key))
	{
		swap(heap, j, heap->parent(j));
		j = heap->parent(j);
	}
}

// swaps the item at the start of the heap with the last item and 
// then decreases size and returns the "removed" item
ELEMENT* Heap::extractMin(Heap* heap)
{
	ELEMENT* extract = heap->H[1];
	if (heap->size > 0)
		swap(heap, 1, size);
	heap->size--;
	return extract;
}

// changes the value of an element in the heap and then swaps 
// values up the heap to make sure it stays as a heap
void Heap::decreaseKey(Heap* heap, int index, int value)
{
	heap->H[index]->key = value;
	int j = index;
	while ((j > 1) && (heap->H[j]->key < heap->H[heap->parent(j)]->key))
	{
		swap(heap, j, heap->parent(j));
		j = heap->parent(j);
	}
}

// each call it checks whether the smallest value is on the left
// or right child, then it swaps it with the index its currently
// at if the smallest value found is different from the index
void Heap::minHeapify(Heap* heap, int index)
{
	numCalls++;
	int L = heap->left(index);
	int R = heap->right(index);
	int smallest = index;

	if ((L <= heap->size) && (heap->H[L]->key < heap->H[index]->key))
		smallest = L;
	if ((R <= heap->size) && (heap->H[R]->key < heap->H[smallest]->key))
		smallest = R;

	if (smallest != index)
	{
		heap->swap(heap, smallest, index);
		heap->minHeapify(heap, smallest);
	}
}

// calls minheapify from the middle of the heap to the top in order
// to make sure the array is a min heap
void Heap::buildHeap(Heap* heap)
{
	int startIndex = floor((heap->size)/2);
	for (int i = startIndex; i > 0; i--)
		heap->minHeapify(heap, i);
}

// swaps the element pointers at the specified indexes of x and y
void Heap::swap(Heap* heap, int x, int y)
{
	ELEMENT* ptr = heap->H[x];
	heap->H[x] = heap->H[y];
	heap->H[y] = ptr;
}

// returns the index of the parent of n
int Heap::parent(int n)
{
	return floor(n / 2);
}

// returns the index of the left child of n
int Heap::left(int n)
{
	return n*2;
}

// returns the index of the right child of n
int Heap::right(int n)
{
	return (n*2)+1;
}

