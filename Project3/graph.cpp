#include "graph.h"

Graph::Graph()
{

}

Graph::Graph(int n, int m)
{
	adjList = (Node**)malloc((n + 1) * sizeof(Node*));
	for (int i = 0; i < n + 1; i++)
		adjList[i] = NULL;
}

void Graph::insertNode(int x, int y, int edgeWeight)
{
	Node* newNode = new Node(y, edgeWeight);
	newNode->next = adjList[x];
	adjList[x] = newNode;
	if (!directed)
	{
		Node* newNode2 = new Node(x, edgeWeight);
		newNode2->next = adjList[y];
		adjList[y] = newNode2;
	}
}

void Graph::setDirected(bool y)
{
	directed = y;
}
