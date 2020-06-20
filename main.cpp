#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>

constexpr auto EDGES_MAX = 1024;

int main() {
  std::ifstream input_file("input.txt");

  try {
    if (!input_file.good()) {
      throw "File was not opened succesfully";
    }

    std::cout << "File was successfully opened" << std::endl;

    int starting_node, total_nodes, total_edges;
    input_file >> starting_node >> total_nodes >> total_edges;

    if (EDGES_MAX < total_edges) {
      throw "The number of edges it too high. Numer of edges is limited to: 1024";
    }

    Graph *graph = new Graph(false, total_edges);
    int temp_node_a, temp_node_b, temp_edge_weight;

    int *parent = new int [total_edges + 1]; // initialized by InitVars()
    int *distance = new int [total_edges + 1]; // initialized by InitVars()

    for (int i = 0; i < total_edges; i++) {
      input_file >> temp_node_a >> temp_node_b >> temp_edge_weight;
      
      if ((temp_node_a > total_nodes) || (temp_node_b > total_nodes)) {
        throw "Incorrect number of a node";
      } else if (temp_node_a == temp_node_b) {
        throw "You cannot create inbound and outbound highway from the same city";
      } else if (temp_edge_weight <= 0) {
        throw "Weight must be positive";
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

      delete [] parent;
      delete (parent);

      delete [] distance;
      delete (distance);

    } catch (const char *msg) {
      std::cerr << msg << std::endl;
      return 1;
    }

  return 0;
}
