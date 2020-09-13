#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <limits>

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
			throw "Plik nie zostal otwarty poprawnie";
		}

		std::cout << "Plik zostal otwarty poprawnie" << std::endl;

		std::vector<int> distance;
		std::vector<int> parent;

		auto starting_node = 0;
		auto total_nodes = 0;
		auto total_edges = 0;
		input_file >> starting_node >> total_nodes >> total_edges;

		if (edges_max < total_edges)
		{
			throw "Liczba krawedzi jest zbyt duza. Maksymalna wartosc to: 1024";
		}

		std::unique_ptr<graph_class> my_graph(new graph_class(false, total_nodes));
		auto temp_node_a = 0;
		auto temp_node_b = 0;
		auto temp_edge_weight = 0;
		int edges_tab[total_edges][3];

		for (auto i = 0; i < total_edges; i++)
		{
			input_file >> temp_node_a >> temp_node_b >> temp_edge_weight;
			my_graph->insert_edge(temp_node_a, temp_node_b, temp_edge_weight, false);
			edges_tab[i][0] = temp_node_a;
			edges_tab[i][1] = temp_node_b;
			edges_tab[i][2] = temp_edge_weight;
			if ((temp_node_a > total_nodes) || (temp_node_b > total_nodes) || (temp_node_b < 1) || (temp_node_a < 1))
			{
				throw "Niepoprawny numer wierzcholka (wierzcholki powinny byc numerowane w kolejnosci rosnacej)";
			}
			if (weight_max < temp_edge_weight)
			{
				throw "Waga krawedzi jest zbyt duza. Maksymalna wartosc to: 100 000";
			}
		}
		
		auto best_distance = std::numeric_limits<int>::max();
		auto best_iteration = -1;

		std::unique_ptr<graph_class> current_graph(new graph_class(*my_graph));

		for(auto i = 0; i < total_edges; i++)
		{
			std::unique_ptr<graph_class> current_graph(new graph_class(*my_graph));
			current_graph->remove_edge(edges_tab[i][0], edges_tab[i][1], false);
			std::unique_ptr<network_class> my_network(new network_class(current_graph, starting_node));
			if(my_network->is_connected == true){
				if(best_distance > my_network->sum_distances())
				{
					best_distance = my_network->sum_distances();
					best_iteration = i;
				}
			}
		}

		if (best_iteration != -1)
		{
			std::cout << "Najlepiej usunac polaczenie miedzy miastami " << edges_tab[best_iteration][0] << " i " << edges_tab[best_iteration][1] <<
			" o wadze " << edges_tab[best_iteration][2] << std::endl;
			std::cout << "Suma odleglosci od stolicy (wierzcholek numer " << starting_node << ") wyniesie wtedy " << best_distance << std::endl;
		}else
		{
			std::cout << "Nie udalo sie znalezc dozwolonego miejsca na pas startowy" << std::endl;
		}
	}

	catch (const char* msg)
	{
		std::cerr << msg << std::endl;
		return 1;
	}

	std::cin.get(); 

	return 0;
}
