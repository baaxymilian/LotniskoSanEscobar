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

graph_class::graph_class()
{
	this->directed = false;
	this->node_number = 0;
	this->edges = new edge_node*;
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
	this->edges = new edge_node*[parent.node_number + 1];
	for (auto i = 1; i < this->node_number + 1; i++)
	{
		this->edges[i] = new edge_node;
	}
	for (auto v_tmp = 1; v_tmp < node_number + 1; v_tmp++)
	{
		auto* tmp = parent.edges[v_tmp];
		while(tmp->next != nullptr)
		{
			this->insert_edge(tmp->number, v_tmp, tmp->weight, true);
			tmp = tmp->next;
        }
	}
}

auto graph_class::insert_edge(const int x, const int y, const int weight, const bool is_directed) const -> void
{
	if (x == y)
	{
		throw "You cannot create inbound and outbound highway from the same city";
	}
	if (weight <= 0 || weight >= 100000)
	{
		throw "Weight must be positive and less than 100 000";
	}
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

auto graph_class::remove_edge(const int x, const int y, const bool is_directed) const -> void
{
	if (x > 0 && x < (this->node_number + 1) && y > 0 && y < (this->node_number + 1))
	{
		auto* tmp = this->edges[x];
		auto* prev_tmp = tmp;
		auto valid_flag = false;

		while (tmp != nullptr)
		{
			const auto v_neighbor = tmp->number;
			if (v_neighbor == y)
			{
				valid_flag = true;
				break;
			}
			prev_tmp = tmp;
			tmp = tmp->next;
		}

		if (tmp == this->edges[x])
		{
			this->edges[x] = tmp->next;
		}else
		{
			prev_tmp->next = tmp->next;
		}
		delete tmp;

		if (!valid_flag)
		{
			throw "Nodes are not connected, cannot remove edge";
		}else{
			if (!is_directed)
			{
				remove_edge(y, x, true);
			}
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
	std::cout << std::endl;
}
