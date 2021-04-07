#include "graph.h"

// default constructor
Graph::Graph()
{
	adjList = NULL;
	directed = false;
}

// constructor i will use
Graph::Graph(int n, std::string d)
{
	directed = direction(d);
	adjList = (Node**)calloc(n+1, sizeof(Node*));
	for (int i = 1; i <= n; i++)
		adjList[i] = NULL;
}

bool Graph::direction(std::string d)
{
	if (d == "directed" || "Directed")
		return true;
	return false;
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
