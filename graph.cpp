#include "graph.h"

EdgeNode::EdgeNode() {
	this->number = 0;
	this->weight = 0;
	this->next = nullptr;
}

EdgeNode::EdgeNode(int number, int weight) {
	this->number = number;
	this->weight = weight;
	this->next = nullptr;
}

EdgeNode::EdgeNode(EdgeNode& parent) {
	this->number = parent.number;
	this->weight = parent.weight;
}

Graph::Graph(bool directed, int nodeNumber) {

	this->directed = directed;
	this->nodeNumber = nodeNumber;
	this->edges = new EdgeNode* [nodeNumber + 1];
	for (int i = 0; i < this->nodeNumber + 1; i++)
		this->edges[i] = new EdgeNode;
}

Graph::Graph(Graph& parent) {
	int x;
	int y;
	int weight;

	this->directed = parent.directed;
	this->nodeNumber = parent.nodeNumber;
}

void Graph::InsertEdge(int x, int y, int weight, bool directed) {
	if (x > 0 && x < (this->nodeNumber + 1) && y>0 && y < (this->nodeNumber + 1)) {

		EdgeNode *edge = new EdgeNode(y, weight);
		edge->next = this->edges[x];
		this->edges[x] = edge;
		if (!directed)
			InsertEdge(y, x, weight, true);
	}
}

void Graph::print() const{
	for (int v = 1; v < this->nodeNumber + 1; v++) {
		if (this->edges[v] != nullptr) {
			std::cout << "Vertex" << v << " has neighbours: " << std::endl;
			EdgeNode *current = this->edges[v];
			while (current != nullptr) {
				std::cout << current->number << " (" << current->weight << ")" << std::endl;
				current = current->next;
			}
		}
	}
}

void InitVars(bool discovered[], int distance[], int parent[], int graphSize) {
  for (int i = 1; i < graphSize + 1; i++) {
	discovered[i] = false;
    distance[i] = std::numeric_limits<int>::max();
    parent[i] = -1;
  }
}

void DijkstraAlgorithm(Graph* g, int parent[], int distance[], int start) {
	bool discovered[g->nodeNumber + 1];
	EdgeNode *tmp;

	int vTMP = 0;
	int vNeighbour;
	int weight;
	int smallestDistance;

	InitVars(discovered, distance, parent, g->nodeNumber);

	while (discovered[vTMP] == false) {
		tmp = g->edges[vTMP];

		while (tmp != nullptr) {
			vNeighbour = tmp->number;
			weight = tmp->weight;
			if ((distance[vTMP] + weight) < distance[vNeighbour]) {
				distance[vNeighbour] = distance[vTMP] + weight;
				parent[vNeighbour] = vTMP;
			}
			tmp = tmp->next;
		}

		smallestDistance = std::numeric_limits<int>::max();
		for (int i = 1; i < (g->nodeNumber); i++) {
			if (!discovered[i] && (distance[i] < smallestDistance)) {
				vTMP = i;
				smallestDistance = distance[i];
			}
		}
	}
	/* DO PÓŹNIEJSZEGO UŻYCIA
	for (int i = 0; i < g->nodeNumber + 1; i++)
      delete[] discovered[i];
  		delete[] discovered;
		  */
}

void PrintShortestPath(int v, int parent[], int graphNumber) {
	if (v > 0 && (v < graphNumber + 1) && parent[v] != -1) {
		std::cout << parent[v] << " ";
		PrintShortestPath(parent[v], parent, graphNumber);
	}
}

void PrintDistances(int start, int distance[], int graphNumber) {
	for (int i = 1; i < graphNumber + 1; i++) {
		if (distance[i] != std::numeric_limits<int>::max()) {
			std::cout << "Shortest distance from " << start << "to" << i << "is: " << distance[i] << std::endl;
		}
	}
}

void TestGraph(void) {
	const int nodeNumber = 10;

	Graph *myGraph = new Graph(false, nodeNumber);

	int parent[nodeNumber + 1];
	int distance[nodeNumber + 1];

	int start = 1;

	myGraph->InsertEdge(1, 2, 6, false);
	myGraph->InsertEdge(1, 3, 2, false);
	myGraph->InsertEdge(3, 2, 5, false);
	myGraph->InsertEdge(3, 4, 1, false);
	myGraph->InsertEdge(2, 4, 3, false);
	myGraph->InsertEdge(4, 5, 2, false);

	//Wykonaj algorytm Dijkstry
	DijkstraAlgorithm(myGraph, parent, distance, start);

	//Wypisz najkrótszą ścieżkę z wierzchołka 1 do 5
	PrintShortestPath(5, parent, nodeNumber);

	//Wypisz dystanse od wierzchołka startowego do wszystkich innych.
	//Wypisz dystanse od wierzchołka startowego do wszystkich innych.
	PrintDistances(start, distance, nodeNumber);
}
