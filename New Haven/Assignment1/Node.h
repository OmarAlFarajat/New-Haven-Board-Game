#pragma once
#include <cstddef>

enum class Direction { LEFT, RIGHT, UP, DOWN };
enum class NodeType { TILE, RESOURCE, BUILDING};

class Node
{
	int* id;
	bool* visited;	//	For DFS
	bool* enabled;	//	For map loading, debugging, and placement
	bool* occupied; //	For placement

	// Edges
	Node* up;
	Node* down;
	Node* left;
	Node* right;

public:
	Node();
	~Node();

	// Setters
	void addEdge(Node*, Direction);
	void setOccupied(bool occupied) { *this->occupied = occupied; }

	// Getters
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

