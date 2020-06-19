#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>

constexpr auto EDGES_MAX = 1024;

int main() {
  std::ifstream input_file("input.txt");

  int starting_node, total_nodes, total_edges;

  try {
    if (!input_file.good()) {
      throw "File was not opened succesfully";
    }

    std::cout << "Plik otwarty poprawnie" << std::endl;

    input_file >> starting_node >> total_nodes >> total_edges;

    if (EDGES_MAX < total_edges) {
      throw "The number of edges it too high. Numer of edges is limited to: 1024";
    }

    Graph *graph = new Graph(false, total_edges);
    int temp_node_a, temp_node_b, temp_edge_weight;

    int parent[total_edges + 1];
    int distance[total_edges + 1];

    for (int i = 0; i < total_edges; i++) {
      input_file >> temp_node_a >> temp_node_b >> temp_edge_weight;
      
      if ((temp_node_a > total_nodes) || (temp_node_b > total_nodes)) {
        throw "Nieprawidlowy numer wierzcholka!";
      } else if (temp_node_a == temp_node_b) {
        throw "Nie mozna utworzyc autostrady wychodzacej i wchodzacej do "
              "tego samego miasta";
      } else if (temp_edge_weight <= 0) {
        throw "Podano niedodatnia wage krawedzi";
      }
    } 
      graph->InsertEdge(temp_node_a, temp_node_b, temp_edge_weight, 0);
    
      // sprawdzenie poprawnosci wczytanych wartosci
      // indeks 0 - pierwszy wierzcholek
      // indeks 1 - drugi wierzcholek
      // indeks 2 - waga polaczenia
      graph->print();

      DijkstraAlgorithm(graph, parent, distance, 1);

      PrintShortestPath(5, parent, total_edges);

      PrintDistances(1, distance, total_edges);

      TestGraph();

    } catch (const char *msg) {
      std::cerr << msg << std::endl;
      return 1;
    }

  return 0;
}
