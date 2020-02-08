#pragma once
#include <vector>
#include "Node.h"

class Graph
{
	std::vector<Node*> nodes; 
	int* number_of_nodes;

public:
	void addNode(Node*);
	Graph();
	~Graph();
	void makeSquareGrid(int);
	void printGrid(int);
	bool isConnected_DFS(Node*);
	Node* getRootNode() {
		return nodes[0];
	}
	int getNumberOfNodes() { 
		return *number_of_nodes; 
	};
};

