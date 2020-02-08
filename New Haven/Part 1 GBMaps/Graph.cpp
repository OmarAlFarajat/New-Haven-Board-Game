#include "Graph.h"
#include "Node.h"
#include <iostream>

// A recursive depth-first search
bool Graph::isConnected_DFS(Node* node)
{
	// Mark the node as visited
	*node->visited = true;

	// Recursive calls
	// If connection is not null and the connected node has not been visited 
	if (node->up && !*node->up->visited)
		isConnected_DFS(node->up);

	if (node->down && !*node->down->visited)
		isConnected_DFS(node->down);

	if (node->left && !*node->left->visited)
		isConnected_DFS(node->left);

	if (node->right && !*node->right->visited)
		isConnected_DFS(node->right);

	// Count how many nodes have been visited
	int counter = 0;
	for (int i = 0; i < nodes.size(); i++) 
		if (*nodes[i]->visited) 
			counter++;

	// Compare it with the total number of nodes. 
	// If number of nodes visisted is equal to total number of nodes, then graph is connected.  
	if (counter == *number_of_nodes)
		return true;
	else
		return false; 
	
}

void Graph::addNode(Node* node)
{
	*node->id = *number_of_nodes;
	(*number_of_nodes)++;
	nodes.push_back(node);
}

// Makes a square grid of size length x length. 
void Graph::makeSquareGrid(int length)
{
	// First create all the nodes
	int totalNodes = length * length;
	for (int i = 0; i < totalNodes; i++)
	{
		this->addNode(new Node());
	}

	// Create all the connections (edges)
	for (int i = 0; i < totalNodes; i++)
	{		
		if(i-length >= 0)
			nodes[i]->addConnection(nodes[i-length], Direction::UP);
		if (i + length <= totalNodes - 1)
			nodes[i]->addConnection(nodes[i+length], Direction::DOWN);
		if(i-1 >= 0)
			nodes[i]->addConnection(nodes[i-1], Direction::LEFT);
		if(i+1 <= totalNodes - 1)
			nodes[i]->addConnection(nodes[i+1], Direction::RIGHT);	
	}

}

// Debugging function to print the grid graph
void Graph::printGrid(int length)
{
	int totalNodes = length * length;

	for (int i = 0; i < totalNodes - length + 1; i+=length) {
		// Format id(up, down, left, right, visited)
		for (int j = 0; j < length; j++) {
			std::string up = nodes[i + j]->up ? std::to_string(*nodes[i + j]->up->id) : "x";
			std::string down = nodes[i + j]->down ? std::to_string(*nodes[i + j]->down->id) : "x";
			std::string left = nodes[i + j]->left ? std::to_string(*nodes[i + j]->left->id) : "x";
			std::string right = nodes[i + j]->right ? std::to_string(*nodes[i + j]->right->id) : "x";
			std::string visited = *nodes[i + j]->visited ? "Y" : "N";
			std::cout << *nodes[i+j]->id << "(" 
			<< up << ","
			<< down << ","
			<< left << ","
			<< right << ","
			<< visited << ")"
			<< "  ||\t";
		}
		std::cout << std::endl; 
	}
	std::cout << std::endl;
}

Graph::Graph()
{
	number_of_nodes = new int(0); 
}

Graph::~Graph()
{
}
