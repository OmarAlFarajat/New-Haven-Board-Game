#pragma once
#include <vector>
#include <string>

enum class Direction { LEFT, RIGHT, UP, DOWN };
enum class NodeType { MAP, TILE, RESOURCE };
class Node
{
	int* id; 
	bool* visited;	// For DFS
	bool* enabled; 

	Node* up; 
	Node* down;
	Node* left; 
	Node* right;

public:
	Node();
	~Node();
	void addConnection(Node*, Direction);

	friend class Graph; 
};

