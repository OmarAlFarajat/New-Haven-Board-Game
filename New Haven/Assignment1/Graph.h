#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Node.h"
#include "Resources.h"

class Graph
{
	std::vector<Node*>* nodes;
	int* numEnabledNodes;
	int* length;
	int* height;

public:
	Graph();
	~Graph();
	// Initializing functions
	void makeGridGraph(int length, int height, NodeType nodeType);
	void addNode(Node*);
	void linkResourceNodes(Graph* graph);
	// Debug
	void printGridGraph(bool verbose);
	bool isConnected_DFS(Node*);
	bool depthFirstSearch(Node*);
	void DFS_ByType(Resource* node);
	// Mutators
	void disableNode(int id);
	void enableNode(int id);
	void resetAllVisited();
	// Inline getters
	Node* getRootNode() { return nodes[0][0]; }
	Node* getNode(int index) { return nodes[0][index]; }
	std::vector<Node*>* getNodes() { return nodes; }
	int getNumEnabledNodes() { return *numEnabledNodes; }
	int getLength() { return *length; }
	int getHeight() { return *height; }
};