#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Node.h"

class Graph
{
	std::vector<Node*>* nodes;
	int* number_of_nodes;
	int* length;
	int* height;

public:
	void addNode(Node*);
	Graph();
	~Graph();
	void makeGridGraph(int length, int height, NodeType nodeType);
	void printGridGraph(bool verbose);
	bool isConnected_DFS(Node*);
	Node* getRootNode() {return nodes[0][0]; }
	Node* getNode(int index) { return nodes[0][index]; };
	int getNumberOfNodes() { return *number_of_nodes; };
	void resetAllVisited();
};