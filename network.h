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
	std::vector<int> distance;
    std::vector<int> parent;

    network_class();
	network_class(std::unique_ptr<graph_class>&, const int);

    auto print_shortest_path(int) const -> void;
    auto print_distances() const -> void;

};

#endif // !NETWORK_H
