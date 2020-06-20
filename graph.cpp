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
	for (auto i = 0; i < this->node_number + 1; i++)
	{
		this->edges[i] = new edge_node;
	}
}

graph_class::graph_class(const graph_class& parent)
{
	this->directed = parent.directed;
	this->node_number = parent.node_number;
	this->edges = new edge_node*[node_number + 1];
	for (auto i = 0; i < this->node_number + 1; i++)
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
			std::cout << "Vertex" << v << " has neighbors: " << std::endl;
			auto* current = this->edges[v];
			while (current != nullptr)
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
	for (auto i = 1; i < graph_size + 1; i++)
	{
		discovered.push_back(false);
		distance.push_back(std::numeric_limits<int>::max());
		parent.push_back(-1);
	}
}

auto dijkstra_algorithm(std::unique_ptr<graph_class>& g, std::vector<int> parent, std::vector<int> distance,
                        int start) -> void
{
	std::vector<bool> discovered;

	auto v_tmp = 0;

	init_vars(discovered, distance, parent, g->node_number);

	while (discovered[v_tmp] == false)
	{
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
}

auto print_shortest_path(const int v, std::vector<int> parent, const int graph_number) -> void
{
	if (v > 0 && v < graph_number + 1 && parent[v] != -1)
	{
		std::cout << parent[v] << " ";
		print_shortest_path(parent[v], parent, graph_number);
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

auto test_graph(void) -> void
{
	const auto node_number = 10;

	std::unique_ptr<graph_class> my_graph(new graph_class(false, node_number));

	std::vector<int> parent;
	std::vector<int> distance;

	const auto start = 1;

	my_graph->insert_edge(1, 2, 6, false);
	my_graph->insert_edge(1, 3, 2, false);
	my_graph->insert_edge(3, 2, 5, false);
	my_graph->insert_edge(3, 4, 1, false);
	my_graph->insert_edge(2, 4, 3, false);
	my_graph->insert_edge(4, 5, 2, false);

	//Wykonaj algorytm Dijkstry
	dijkstra_algorithm(my_graph, parent, distance, start);

	//Wypisz najkrótszą ścieżkę z wierzchołka 1 do 5
	print_shortest_path(5, parent, node_number);

	//Wypisz dystanse od wierzchołka startowego do wszystkich innych.
	print_distances(start, distance, node_number);
}
