#pragma once
#include <cstddef>

enum class Direction { LEFT, RIGHT, UP, DOWN };
enum class NodeType { TILE, RESOURCE, BUILDING};

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
	bool isVisited() { return *visited; }
	bool isEnabled() { return *enabled; }
	bool isOccupied() { return *occupied; }
	Node* getUp() { return up; }
	Node* getDown() { return down; }
	Node* getLeft() { return left; }
	Node* getRight() { return right; }

	friend class Graph;
};

