#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cfloat>

#include "heap.h"
#include "util.h"
#include "vertex.h"
#include "graph.h"
#include "node.h"

using namespace std;

//void garbageCollector(Heap* heap);
int dijkstra(Graph* g, Heap* h, int source, int dest, int flag);
int writePath(Heap* h, int, int, int, int, int);
void freeMemory(Heap* h, int numVertices);

int main(int argc, char* argv[])
{
	// variable initialization
	int cmd, source, destination, flag;//, err;

	int lastSource = -1;
	int lastDest = -1;
	int err = 0;

	Graph* graph = initializeGraph( argv[1], argv[2]);
	Heap* h = NULL;
	//graph->print();

	// loops until nextcommand returns a 0
	while (nextCommand(&cmd, &source, &destination, &flag)) 
	{
		switch (cmd)
		{
			case 1:
				// free memory of heap right here if it is not NULL
				if (h != NULL && err != -1)
					freeMemory(h, graph->getVertices());
				h = h->initialize(graph->getVertices());
				err = dijkstra(graph, h, source, destination, flag);
				lastSource = source;
				lastDest = destination;
				break;
			case 2:
				if (lastSource == -1) {
					cout << "Error: no path computation done\n";
					break;
				}
				if (source != lastSource || source == destination || destination > graph->getVertices() || destination < 1) {
					cout << "Error: invalid source destination pair\n";
					break;
				}
				writePath(h, source, lastSource, destination, lastDest, graph->getVertices());
				break;
			default:
				break;
		}
	}
}

void freeMemory(Heap* h, int numVertices)
{
	for (int i = 1; i <= numVertices; i++)
		free(h->V[i]);	
	free(h->V);
	free(h->H);
	free(h);
	h = NULL;
}

int writePath(Heap* h, int source, int lastSource, int dest, int lastDest, int numVertices)
{
	int current = dest;
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
	{
		if (h->V[dest]->getColor() == 0)
		{
			if ((lastDest < 1) || (lastDest > numVertices )|| (lastDest == dest))//h->V[numVertices]->getColor() > 0 && lastDest >= dest) 
			{
				cout << "No " << source << "-" << dest << " path exists.\n";
				return -1;
			}
			else 
			{
				cout << "No " << source << "-" << dest << " path has been computed.\n";
				return -1;
			}
		}
	}

	Node* temp = path;
	if (h->V[dest]->getColor() == 1)
		cout << "Path not known to be shortest: " << "<";
	else if (h->V[dest]->getColor() == 2)
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

	// free memory 
	while (path)
	{
		Node* del = path;
		path = path->next;
		free(del);
	}

	return 1;
}

int dijkstra(Graph* g, Heap* h, int source, int dest, int flag)
{
	ELEMENT* list = NULL;
	if (source > g->getVertices() || source < 1 || source > g->getVertices() || dest == source || flag < 0 || flag > 1)
	{
		cout << "Error: invalid find query\n";
		return -1;
	}
	// initialize vertex list held in heap class
	//cout << "1" << endl;
	for (int i = 1; i <= g->getVertices(); i++)
	{
		h->V[i] = (Vertex*)malloc(sizeof(Vertex));
		h->V[i]->setColor(0);
		h->V[i]->setDistance(FLT_MAX);
		h->V[i]->setPi(-1);
	}
	//cout << "2" << endl;
	h->V[source]->setDistance(0);
	//cout << "3" << endl;
	h->V[source]->setColor(1);
	//cout << "4" << endl;
	ELEMENT* temp = (ELEMENT*)malloc(sizeof(ELEMENT));
	temp->key = 0;
	temp->vertex = source;
	//cout << "5" << endl;
	h->insert(h, temp);
	//cout << "source: " << source << endl;
	//cout << h->H[source]->key;
	//cout << "6" << endl;
	if (flag)
		printf("Insert vertex %d, key=%12.4f\n", source, h->H[1]->key);
	//cout << "7" << endl;
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
		{
			free(temp);
			return 0;
		}
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
				ele->next = list;
				list = ele;
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

	while (list)
	{
		ELEMENT* del = list;
		list = list->next;
		free(del);
	}

	free(temp);
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
			case 'c':
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