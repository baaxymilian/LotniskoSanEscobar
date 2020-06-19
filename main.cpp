#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>


#define EDGES_MAX 1024

int main() {
  std::fstream input_file;
  input_file.open("input.txt", std::ios::in | std::ios::out);
  std::string display;
  int X, Y, Z;

  if (input_file.good() == true) {
    std::cout << "Plik otwarty poprawnie" << std::endl;
    // tu operacje na pliku (zapis/odczyt)
    // X - wierzchołek startowy
    // Y - łączna liczba wierzchołków
    // Z - łączna liczba krawędzi
    input_file >> X >> Y >> Z;
    Graph* graph = new Graph(false, Z);
    int temp_node_a, temp_node_b, temp_edge_weight;

    int parent[Z + 1];
    int distance[Z + 1];

    for (int i = 0; i < Z; i++) {
      input_file >> temp_node_a >> temp_node_b >> temp_edge_weight;
      try {
        if ((temp_node_a > Y) || (temp_node_b > Y)) {
          throw "Nieprawidlowy numer wierzcholka!";
        } else if (temp_node_a == temp_node_b) {
          throw "Nie mozna utworzyc autostrady wychodzacej i wchodzacej do "
                "tego samego miasta";
        } else if (temp_edge_weight <= 0) {
          throw "Podano niedodatnia wage krawedzi";
        }
      } catch (const char *msg) {
        std::cerr << msg << std::endl;
        input_file.close();
        return 1;
      }
      graph->InsertEdge(temp_node_a, temp_node_b, temp_edge_weight, 0);
    }
    // sprawdzenie poprawnosci wczytanych wartosci
    // indeks 0 - pierwszy wierzcholek
    // indeks 1 - drugi wierzcholek
    // indeks 2 - waga polaczenia
    graph->print();

    DijkstraAlgorithm(graph, parent, distance, 1);

    PrintShortestPath(5, parent, Z);

    PrintDistances(1, distance, Z);

    TestGraph();

    input_file.close();
  } else {
    std::cout << "Plik nie zostal otwarty poprawnie" << std::endl;
    return 1;
  }
  return 0;
}
