#pragma once
#include <cstddef>

enum class Direction { LEFT, RIGHT, UP, DOWN };
enum class NodeType { TILE, RESOURCE };

class Node
{
	int* id;
	bool* visited;	// For DFS
	bool* enabled; 

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

