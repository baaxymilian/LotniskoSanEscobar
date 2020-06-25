#include <iostream>
#include <limits>

#include "network.h"
#include "graph.h"

constexpr int weight_max = 100000;

network_class::network_class()
{   
    std::vector<int> empty_v;
	this->graph = new graph_class;
    this->capital_id = 0;
    this->distance = empty_v;
    this->parent = empty_v;

}

network_class::network_class(std::unique_ptr<graph_class>& g, const int capital_id)
{
	this->graph = new graph_class(*g);
	this->capital_id = capital_id;

	/*
	Begin Dijkstra algorithm
	*/
	std::vector<bool> discovered;
	std::vector<int> distance;
	std::vector<int> parent;

	auto v_tmp = capital_id;

	for (auto i = 0; i < this->graph->node_number + 1; i++)
	{
		discovered.push_back(false);
		distance.push_back(weight_max);
		parent.push_back(-1);			
	}
	distance[this->capital_id] = 0;


	while (discovered[v_tmp] == false)
	{
		discovered[v_tmp] = true;
		auto* tmp = this->graph->edges[v_tmp];

		while (tmp != nullptr)
		{
			const auto v_neighbor = tmp->number;
			const auto weight = tmp->weight;
			if (distance[v_tmp] + weight < distance[v_neighbor])
			{
				distance[v_neighbor] = distance[v_tmp] + weight;
				parent[v_neighbor] = v_tmp;
			}
			tmp = tmp->next;
		}

		auto smallest_distance = std::numeric_limits<int>::max();
		for (auto i = 1; i < this->graph->node_number + 1; i++)
		{
			if (!discovered[i] && (distance[i] < smallest_distance))
			{
				v_tmp = i;
				smallest_distance = distance[i];
			}
		}
		
	}

	/*
	End Dijkstra Algorithm
	*/

	this->distance = distance;
	this->parent = parent;
}

auto network_class::sum_distances() const -> int
{
	auto sum = 0;
	for (auto i = 1; i < this->graph->node_number + 1; i++)
	{
		if (distance[i] != std::numeric_limits<int>::max() && i != capital_id)
		{
			sum += distance[i];
		}
	}
	return sum;
}

auto network_class::print_shortest_path(const int start) const -> void
{
	std::cout << start; 
	auto tmp = start;
	while (tmp != capital_id)
	{
		std::cout << "->" << this->parent[tmp];
		tmp = this->parent[tmp];
	}
	std::cout << std::endl; 
}

auto network_class::print_distances() const -> void
{
	for (auto i = 1; i < this->graph->node_number + 1; i++)
	{
		if (distance[i] != std::numeric_limits<int>::max() && i != capital_id)
		{
			std::cout << "Shortest distance from " << this->capital_id << " to " << i << " is: " << distance[i] << std::endl;
		}
	}

}
