#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>

constexpr auto EDGES_MAX = 1024;

int main() {
  std::fstream input_file;
  input_file.open("input.txt", std::ios::in | std::ios::out);

  int X, Y, Z;

  try {
    if (!input_file.good()) {
      throw "File was not opened succesfully";
    }

    std::cout << "Plik otwarty poprawnie" << std::endl;
    // tu operacje na pliku (zapis/odczyt)
    // X - wierzchołek startowy
    // Y - łączna liczba wierzchołków
    // Z - łączna liczba krawędzi
    input_file >> X >> Y >> Z;

    if (EDGES_MAX < Z) {
      throw "The number of edges it too high. Numer of edges is limited to: 1024";
    }

    Graph* graph = new Graph(false, Z);
    int temp_node_a, temp_node_b, temp_edge_weight;

    int parent[Z + 1];
    int distance[Z + 1];

    for (int i = 0; i < Z; i++) {
      input_file >> temp_node_a >> temp_node_b >> temp_edge_weight;
      
        if ((temp_node_a > Y) || (temp_node_b > Y)) {
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

      PrintShortestPath(5, parent, Z);

      PrintDistances(1, distance, Z);

      TestGraph();

    } catch (const char *msg) {
        std::cerr << msg << std::endl;
        input_file.close();
        return 1;
    }

    input_file.close();
  return 0;
}
