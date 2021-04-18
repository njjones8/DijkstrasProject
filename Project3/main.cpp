#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include "heap.h"
#include "util.h"
#include "vertex.h"
#include "graph.h"
#include "node.h"

using namespace std;

//void garbageCollector(Heap* heap);
int dijkstra(Graph* g, Heap* h, int source, int dest, int flag);
int writePath(Heap* h, int source, int dest);

int main()
{
	// variable initialization
	int cmd, source, destination, flag, err;
	Heap* heap = NULL;
	ELEMENT* element = NULL;

	Graph* graph = initializeGraph();
	Heap* h = NULL;
	//graph->print();

	// loops until nextcommand returns a 0
	while (nextCommand(&cmd, &source, &destination, &flag)) 
	{
		switch (cmd)
		{
			case 1:
				// free memory of heap right here if it is not NULL
				h = h->initialize(graph->getVertices());
				dijkstra(graph, h, source, destination, flag);
				break;
			case 2:
				// check if a find query has been done
				err = writePath(h, source, destination);
				if (err == -1)
					cout << "No " << source << "-" << destination << " path exists.\n";
				break;
			default:
				break;
		}
	}
}

int writePath(Heap* h, int source, int dest)
{
	int current = dest;
	float totalWeight = 0;
	bool found = false;

	Node* path = new Node(dest);

	while (h->V[current]->getPi() != -1 && found == false)
	{
		int prev = h->V[current]->getPi();
		if (h->V[current]->getPi() == source) 
			found = true;
		Node* temp = new Node(prev);
		temp->next = path;
		path = temp;

		current = h->V[current]->getPi();
	}

	if (found == false)
		return -1;

	Node* temp = path;
	cout << "Shortest path: " << "<";
	while (temp)
	{
		cout << temp->num;
		if (temp->next)
			cout << ", ";
		temp = temp->next;
	}
	cout << ">\n";
	printf("The path weight is: %12.4f\n", h->V[dest]->getDistance());

	// free memory of linked list path here

	return 1;
}

int dijkstra(Graph* g, Heap* h, int source, int dest, int flag)
{
	//h = h->initialize(g->getVertices());

	// initialize vertex list held in heap class
	for (int i = 1; i <= g->getVertices(); i++)
	{
		h->V[i] = (Vertex*)malloc(sizeof(Vertex));
		h->V[i]->setColor(0);
		h->V[i]->setDistance((float)INT_MAX);
		h->V[i]->setPi(-1);
	}

	h->V[source]->setDistance(0);
	h->V[source]->setColor(1);

	ELEMENT* temp = (ELEMENT*)malloc(sizeof(ELEMENT));
	temp->key = 0;
	temp->vertex = source;

	h->insert(h, temp);
	if (flag)
		printf("Insert vertex %d, key=%12.4f\n", source, h->H[source]->key);

	bool found = false;
	while ((h->size > 0) && (!found))
	{
		ELEMENT* extractNode = h->extractMin(h);
		int extractIndex = extractNode->vertex;
		//cout << "extractIndex = " << extractIndex << endl;
		if (flag) {
			printf("Delete vertex %d, key=%12.4f\n", extractIndex, extractNode->key);
		}
		Vertex* u = h->V[extractIndex];
		u->setColor(2);
		if (extractIndex == dest)
			return 0;

		Node* edge = g->getList()[extractIndex];

		// traverse through adjacency list while 
		while (edge)
		{
			Vertex* v = h->V[edge->num];
			if (v->getColor() == 0)
			{
				//cout << "edge->num" << edge->num << endl;
				v->setDistance(u->getDistance() + edge->weight);
				v->setPi(extractIndex);
				v->setColor(1);
				ELEMENT* ele = (ELEMENT*)malloc(sizeof(ELEMENT));
				ele->key = v->getDistance();
				ele->vertex = edge->num;
				h->insert(h, ele);
				if (flag)
					printf("Insert vertex %d, key=%12.4f\n", edge->num, v->getDistance());
			}
			else if (v->getDistance() > (u->getDistance() + edge->weight))
			{
				float newDist = u->getDistance() + edge->weight;
				if (flag)
					printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", edge->num, v->getDistance(), newDist);
				v->setDistance(u->getDistance() + edge->weight);
				v->setPi(extractIndex);
				//cout << "Current size of heap: " << h->size << endl;
				//cout << "Setting index " << edge->num << " key to " << v->getDistance() << endl;
				h->decreaseKey(h, v->getPosition(), v->getDistance());
			}
			edge = edge->next;
		}
	}
	return 1;
}
	// loop runs until case S where program free's memory and then exits
	/*while (1)
	{
		// calls nextCommand in util module to find out what the user
		// wants the program to do next
		c = nextCommand(&n, &flag);

		switch (c)
		{
			// stop
			case 's':
			case 'S':
				//garbageCollector(heap); 
				exit(0);

			// initialize heap with capacity n
			/*case 'c':
			case 'C':
				heap = heap->initialize(n);
				break;

			// read file and place elements into dynamically allocated space
			case 'r':
			case 'R':
				readFile.open(inFile);
				if (readFile.fail()) // if file does not open
				{
					cout << "Error: cannot open file for reading" << endl;
					break;
				}
				readFile >> n;

				// checks if heep is NULl before checking the capacity so
				// that program does not crash trying to read capacity of a 
				// NULL object
				if (heap == NULL || heap->capacity < n)
				{
					cout << "Error: heap overflow" << endl;
					readFile.close(); // make sure to close file incase of heap overflow
					break;
				}

				// sets heap size to 0 again to make sure the size is correctly 
				// calculated in the following loop
				heap->size = 0;
				for (int i = 1; i <= n; i++)
				{
					readFile >> number;
					heap->H[i] = (ELEMENT*)malloc(sizeof(ELEMENT));
					heap->H[i]->key = number;
					heap->size++;
				}
				heap->numCalls = 0;
				heap->buildHeap(heap);
				if (flag == 1)
					cout << "Number of Heapify calls: " << heap->numCalls << endl;
				readFile.close(); // closes the file
				break;

			// prints the heap unless the heap is NULL 
			case 'p':
			case 'P':
				if (heap == NULL)
					cout << "Error: heap is NULL" << endl;
				else
					heap->printHeap(heap);
				break;
			
			// writes the heap to a file 
			case 'w':
			case 'W':
				writeFile.open(outFile);
				if (writeFile.fail() || heap == NULL)
				{
					cout << "Error: cannot write" << endl;
					writeFile.close();
					break;
				}
				writeFile << heap->size << endl;
				for (int i = 1; i <= heap->size; i++)
					writeFile << heap->H[i]->key << endl;
				writeFile.close();
				break;
			
			// insert to heap
			case 'i':
			case 'I':
				if (heap == NULL || (heap->size >= heap->capacity))
				{
					cout << "Error: heap is NULL or full" << endl;
					break;
				}
				element = (ELEMENT*)malloc(sizeof(ELEMENT));
				element->key = n;
				heap->insert(heap, element);
				break;

			// removes the minimum item in the heap while making sure the 
			// array stays as a heap
			case 'd':
			case 'D':
				if (heap == NULL || heap->size == 0)
				{
					cout << "Error: heap is NULL or empty" << endl;
					break;
				}
				heap->numCalls = 0;
				element = heap->extractMin(heap);
				heap->minHeapify(heap, 1);
				cout << "Deleted key: " << element->key << endl;
				if (flag == 1)
					cout << "Number of Heapify calls: " << heap->numCalls << endl;
				break;
			
			// decreases key of index at n with the value stored in flag
			// if the index doesnt exist, heap is null or the value at n
			// is already smaller than the value stored at flag, it prints out error
			case 'k':
			case 'K':
				if (heap == NULL || (n > heap->size || n < 1) || flag >= heap->H[n]->key)
				{
					cout << "Error: invalid call to DecreaseKey" << endl;
					break;
				}
				heap->decreaseKey(heap, n, flag);
				break;

			default:
				break;
		}
	}*/

// called before program closes to free all dynamically allocated memory
/*void garbageCollector(Heap *heap)
{
	// makes sure heap is NOT null before freeing memory
	if (heap != NULL)
	{
		for (int i = 1; i <= heap->size; i++)
			free(heap->H[i]);
		free(heap->H);
		free(heap);
	}
}*/