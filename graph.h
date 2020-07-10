/**
  @file graph.h
  @brief Implementation graph in C++.
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

  /* node1, node2, weight, is directed */
  auto insert_edge(int, int, int, bool) const -> void;
  
   /* node1, node2, is directed */
  auto remove_edge(int, int, bool) const -> void;
	
  /*print out graph info*/
  auto print() const -> void;
};

#endif // !GRAPH_H
