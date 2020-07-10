#include <fstream>
#include <iostream>
#include <string>
#include <memory>

#include "network.h"
#include "graph.h"

constexpr int edges_max = 1024;
constexpr int weight_max = 100000;

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

		std::vector<int> distance;
		std::vector<int> parent;

		auto starting_node = 0;
		auto total_nodes = 0;
		auto total_edges = 0;
		input_file >> starting_node >> total_nodes >> total_edges;

		if (edges_max < total_edges)
		{
			throw "The number of edges is too high. Numer of edges is limited to: 1024";
		}

		std::unique_ptr<graph_class> my_graph(new graph_class(false, total_edges));
		auto temp_node_a = 0;
		auto temp_node_b = 0;
		auto temp_edge_weight = 0;
		int edges_tab[total_edges][2];

		for (auto i = 0; i < total_edges; i++)
		{
			input_file >> temp_node_a >> temp_node_b >> temp_edge_weight;
			my_graph->insert_edge(temp_node_a, temp_node_b, temp_edge_weight, false);
			edges_tab[i][0] = temp_node_a;
			edges_tab[i][1] = temp_node_b;
			if ((temp_node_a > total_nodes) || (temp_node_b > total_nodes))
			{
				throw "Incorrect number of a node (nodes should be numbered incrementally)";
			}
			if (weight_max < temp_edge_weight)
			{
				throw "The edge weight is too big. Maximum weight is limited to: 100 000";
			}
		}
		
		// sprawdzenie poprawnosci wczytanych wartosci
		// indeks 0 - pierwszy wierzcholek
		// indeks 1 - drugi wierzcholek
		// indeks 2 - waga polaczenia
		// 

		std::unique_ptr<network_class> my_network(new network_class(my_graph, 1));
		
		//std::unique_ptr<graph_class> new_graph(new graph_class(*my_graph));

		//graph_class* new_graph = new graph_class(*my_graph);

		//my_graph->print();


		//parent = dijkstra_algorithm(my_graph, parent, distance, 1);

		/*std::cout << new_graph->edges[2]->next->number;
		std::cout << my_graph->edges[2]->next->number;

		++my_graph->edges[2]->next->number;

		std::cout << new_graph->edges[2]->next->number;
		std::cout << my_graph->edges[2]->next->number;*/


		//new_graph->print();

		//my_network->print_shortest_path(5);
		//my_network->print_shortest_path(5);


		//my_network->print_distances();
		//my_network->print_is_connected();
		//std::cout << my_network->sum_distances() << std::endl;


	}
	catch (std::string& msg)
	{
		std::cerr << msg << std::endl;
		return 1;
	}

	return 0;
}
