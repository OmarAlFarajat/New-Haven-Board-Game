#pragma once
#include <cstddef>

enum class Direction { LEFT, RIGHT, UP, DOWN };
enum class NodeType { TILE, RESOURCE };

class Node
{
	int* id;
	bool* visited;	// For DFS
	bool* enabled; 
	bool* occupied; 

	// Edges
	Node* up;
	Node* down;
	Node* left;
	Node* right;

public:
	Node();
	~Node();
	void setOccupied(bool occupied) { *this->occupied = occupied; }
	void addEdge(Node*, Direction);
	int getID() { return *id; }
	friend class Graph;
};

