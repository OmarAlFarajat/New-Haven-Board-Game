#pragma once
#include <vector>
#include <string>

enum class Direction { LEFT, RIGHT, UP, DOWN };

class Node
{
	int* id; 
	// For DFS
	bool* visited; 

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

