#include <iostream>
#include <limits>

#include "graph.h"

edge_node::edge_node()
{
	this->number = 0;
	this->weight = 0;
	this->next = nullptr;
}

edge_node::edge_node(const int number, const int weight)
{
	this->number = number;
	this->weight = weight;
	this->next = nullptr;
}

edge_node::edge_node(const edge_node& parent)
{
	this->number = parent.number;
	this->weight = parent.weight;
	this->next = nullptr;
}

graph_class::graph_class(const bool directed, const int node_number)
{
	this->directed = directed;
	this->node_number = node_number;
	this->edges = new edge_node*[node_number + 1];
	for (auto i = 1; i < this->node_number + 1; i++)
	{
		this->edges[i] = new edge_node;
	}
}

graph_class::graph_class(const graph_class& parent)
{
	this->directed = parent.directed;
	this->node_number = parent.node_number;
	this->edges = new edge_node*[node_number + 1];
	for (auto i = 1; i < this->node_number + 1; i++)
	{
		this->edges[i] = new edge_node;
	}
}

auto graph_class::insert_edge(const int x, const int y, const int weight, const bool is_directed) const -> void
{
	if (x > 0 && x < (this->node_number + 1) && y > 0 && y < (this->node_number + 1))
	{
		auto* edge = new edge_node(y, weight);
		edge->next = this->edges[x];
		this->edges[x] = edge;
		if (!is_directed)
		{
			insert_edge(y, x, weight, true);
		}
	}
}

void graph_class::print() const
{
	for (auto v = 1; v < this->node_number + 1; v++)
	{
		if (this->edges[v] != nullptr)
		{
			std::cout << "Node " << v << " has neighbours: " << std::endl;
			auto* current = this->edges[v];
			while (current->number != 0)
			{
				std::cout << current->number << " (" << current->weight << ")" << std::endl;
				current = current->next;
			}
		}
	}
}

auto init_vars(std::vector<bool>& discovered, std::vector<int>& distance, std::vector<int>& parent,
               const int graph_size) -> void
{
	for (auto i = 0; i < graph_size + 1; i++)
	{
		discovered.push_back(false);
		distance.push_back(std::numeric_limits<int>::max());
		parent.push_back(-1);
	}
}

auto dijkstra_algorithm(std::unique_ptr<graph_class>& g, std::vector<int> parent, std::vector<int> distance,
                        int start) -> std::vector<int>
{
	std::vector<bool> discovered;

	auto v_tmp = 1;

	init_vars(discovered, distance, parent, g->node_number);

	while (discovered[v_tmp] == false)
	{
		discovered[v_tmp] = true;
		auto* tmp = g->edges[v_tmp];

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
		for (auto i = 1; i < g->node_number; i++)
		{
			if (!discovered[i] && (distance[i] < smallest_distance))
			{
				v_tmp = i;
				smallest_distance = distance[i];
			}
		}
		
	}
	return parent;
}

auto print_shortest_path(const int v, std::vector<int> parent, const int stop) -> void
{
	std::cout << v; 
	auto tmp = v;
	while(tmp != stop)
	{
		std::cout << "->" << parent[tmp];
		tmp = parent[tmp];
	}
}

auto print_distances(const int start, std::vector<int> distance, const int graph_number) -> void
{
	for (auto i = 1; i < graph_number + 1; i++)
	{
		if (distance[i] != std::numeric_limits<int>::max())
		{
			std::cout << "Shortest distance from " << start << "to" << i << "is: " << distance[i] << std::endl;
		}
	}
}