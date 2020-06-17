/**
  @file graph.h
  @brief Implementation graph in C++.
  @version 1.0
  @date 2020-06-05
  @author Jakub Brzezowski
*/

#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <limits>

/**
  @class EdgeNote
  @brief Impelementation of basics elements of graphs in combination simplified
  usage in graph class.
  @version 1.0
  @date 2020-06-05
  @author Jakub Brzezowski
*/
class EdgeNode {
public:
  int number;     /*!<Number of node*/
  int weight;     /*!<Weight of edge*/
  EdgeNode *next; /*!<Pointer to next node, which represents edge*/

  EdgeNode();
  EdgeNode(int, int);

		EdgeNode();
		EdgeNode(EdgeNode&);
		EdgeNode(int, int);

		~EdgeNode();
};

/**
  @class Graph
  @brief Impelementation of mathematical graph
  @version 1.0
  @date 2020-06-05
  @author Jakub Brzezowski
*/
class Graph {
	private:
		bool directed;
		const int nodeNumber;
	public:
		EdgeNode* edges[nodeNumber + 1];	/*!< Container with edges and nodes*/
		Graph(bool,int);
		Graph(Graph&);
		~Graph();

  Graph(bool, int);
  ~Graph();

  void InsertEdge(int, int, int, bool);
  void print() const;
};

void InitVars(bool discovered[], int distance[], int parent[], int graphSize);
void DijkstraAlgorithm(Graph *g, int parent[], int distance[], int start);

void PrintShortestPath(int v, int parent[], int graphNumber);
void PrintDistances(int start, int distance[], int graphNumber);
void TestGraph(void);

#endif // !GRAPH_H
