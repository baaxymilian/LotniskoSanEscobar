/**
  @file graph.h
  @brief Implementation graph in C++.
  @version 1.0
  @date 2020-06-05
  @author Jakub Brzezowski
*/

#pragma once
#include <vector>
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

	graph_class(bool, int);
	graph_class(const graph_class&);

	auto insert_edge(int, int, int, bool) const -> void;
	auto print() const -> void;
};

auto init_vars(std::vector<bool>& discovered, std::vector<int>& distance, std::vector<int>& parent, const int graph_size) -> void;
auto dijkstra_algorithm(graph_class* g, std::vector<int> parent, std::vector<int> distance, int start) -> void;

auto print_shortest_path(const int v, std::vector<int> parent, const int graph_number) -> void;
auto print_distances(const int start, std::vector<int> distance, const int graph_number) -> void;
auto test_graph(void) -> void;

#endif // !GRAPH_H
