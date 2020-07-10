/**
  @file network.h
  @brief Modeling highway network of San Escobar
  @date 2020-06-21
*/

#pragma once
#include <vector>
#include <memory>
#include "graph.h"
#ifndef NETWORK_H
#define NETWORK_H

class network_class
{
public:
	graph_class* graph; /*!< Custom graph class */
    int capital_id;
    bool is_connected;
	std::vector<int> distance;
    std::vector<int> parent;

    network_class();
	network_class(std::unique_ptr<graph_class>&, const int);

    /* Print out sum of all shortest distances from capital to every other node*/
    auto sum_distances() const -> int;

    /* Print out shortest path from input node to capital node*/
    auto print_shortest_path(int) const -> void;
    
    /* Print out information is graph connected or not*/
    auto print_is_connected() const -> void;
    
    /* Print out distances from capital to every other node*/
    auto print_distances() const -> void;

};

#endif // !NETWORK_H
