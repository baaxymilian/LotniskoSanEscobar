/**
  @file graph.h
  @brief Implementation graph in C++.
  @version 1.0
  @date 2020-06-05
  @author Jakub Brzezowski
*/

#pragma once
#include <vector>
#include <memory>
#ifndef GRAPH_H
#define GRAPH_H

/**
  @class edge_node
  @brief Implementation of basics elements of graphs in combination simplified
  usage in graph class.
  @version 1.0
  @date 2020-06-05
  @author Jakub Brzezowski
*/
class edge_node
{
public:
	int number; /*!<Number of node*/
	int weight; /*!<Weight of edge*/
	edge_node* next; /*!<Pointer to next node, which represents edge*/

	edge_node();
	edge_node(const edge_node&);
	edge_node(int, int);
};

/**
  @class graph_class
  @brief Implementation of mathematical graph
  @version 1.0
  @date 2020-06-05
  @author Jakub Brzezowski
*/
class graph_class
{
public:
	bool directed;
	int node_number;
	edge_node** edges; /*!< Container with edges and nodes*/

  graph_class();
	graph_class(bool, int);
	graph_class(const graph_class&);

	auto insert_edge(int, int, int, bool) const -> void;
	auto print() const -> void;
};

#endif // !GRAPH_H
