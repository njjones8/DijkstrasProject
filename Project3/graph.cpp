#include "graph.h"

// default constructor
Graph::Graph()
{
	numVertices = 0;
	adjList = NULL;
	directed = false;
}

// constructor i will use
Graph::Graph(int n, std::string d)
{
	numVertices = n;
	directed = direction(d);
	adjList = (Node**)calloc(n+1, sizeof(Node*));
	for (int i = 1; i <= n; i++)
		adjList[i] = NULL;
}

bool Graph::direction(std::string d)
{
	if (d == "directed" || d == "Directed")
		return true;
	return false;
}

void Graph::insertNode(int x, int y, float edgeWeight)
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

Node** Graph::getList()
{
	return adjList;
}

// print function i made for debugging purposes
void Graph::print()
{
	for (int i = 1; i <= numVertices; i++)
	{
		Node* temp = adjList[i];
		std::cout << i;
		while (temp != NULL)
		{
			std::cout << " -> ";
			std::cout << temp->num << ":Weight " << temp->weight;
			temp = temp->next;
		}
		std::cout << std::endl;
	}
}

int Graph::getVertices()
{
	return numVertices;
}
