#include <fstream>
#include <iostream>
#include <string>
#include <memory>

#include "graph.h"

constexpr int edges_max = 1024;

auto main() -> int
{
	std::ifstream input_file("input.txt");

	try
	{
		if (!input_file.good())
		{
			throw "File was not opened successfully";
		}

		std::cout << "File was successfully opened" << std::endl;

		auto starting_node = 0;
		auto total_nodes = 0;
		auto total_edges = 0;
		input_file >> starting_node >> total_nodes >> total_edges;

		if (edges_max < total_edges)
		{
			throw "The number of edges it too high. Numer of edges is limited to: 1024";
		}

		std::unique_ptr<graph_class> my_graph(new graph_class(false, total_edges));
		auto temp_node_a = 0;
		auto temp_node_b = 0;
		auto temp_edge_weight = 0;

		std::vector<int> parent;
		std::vector<int> distance;

		for (auto i = 0; i < total_edges; i++)
		{
			input_file >> temp_node_a >> temp_node_b >> temp_edge_weight;
			my_graph->insert_edge(temp_node_a, temp_node_b, temp_edge_weight, false);
			if ((temp_node_a > total_nodes) || (temp_node_b > total_nodes))
			{
				throw "Incorrect number of a node";
			}
			if (temp_node_a == temp_node_b)
			{
				throw "You cannot create inbound and outbound highway from the same city";
			}
			if (temp_edge_weight <= 0)
			{
				throw "Weight must be positive";
			}
		}
		
		// sprawdzenie poprawnosci wczytanych wartosci
		// indeks 0 - pierwszy wierzcholek
		// indeks 1 - drugi wierzcholek
		// indeks 2 - waga polaczenia
		// 
		my_graph->print();

		parent = dijkstra_algorithm(my_graph, parent, distance, 1);

		print_shortest_path(5, parent, 1);

		//print_distances(1, distance, total_edges);

		//test_graph();
	}
	catch (std::string& msg)
	{
		std::cerr << msg << std::endl;
		return 1;
	}

	return 0;
}
