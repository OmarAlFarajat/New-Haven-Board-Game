#pragma once
#include <vector>

// NODE
enum class Direction { LEFT, RIGHT, UP, DOWN };
enum class NodeType { TILE, RESOURCE };
class Node
{
	int* id;
	bool* visited;	// For DFS

	// Edges
	Node* up;
	Node* down;
	Node* left;
	Node* right;

public:
	Node();
	~Node();
	void addEdge(Node*, Direction);

	friend class Graph;
};

// GRAPH
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
	Node* getRootNode() {
		return nodes[0][0];
	}
	Node* getNode(int index) {
		return nodes[0][index];
	};
	int getNumberOfNodes() {
		return *number_of_nodes;
	};
};

class GBMap 
{
public:
	Graph* tileGraph;
	Graph* resourceGraph; 
	GBMap();
	~GBMap();
};


