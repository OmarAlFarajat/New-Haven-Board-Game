#include "Graph.h"
#include "Node.h"
#include <iostream>
#include "Resources.h"

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
void Graph::makeSquareGrid(int length, NodeType nodeType)
{
	// First create all the nodes
	int totalNodes = length * length;
	for (int i = 0; i < totalNodes; i++) {

		switch (nodeType) {
		case NodeType::MAP:
			this->addNode(new Node());
				break;
		case NodeType::RESOURCE:
			this->addNode(new Resource());
			break;
		case NodeType::TILE:
			this->addNode(new HarvestTile());
			break;

		}
	}

	// Create all the connections (edges)
	for (int i = 0; i < totalNodes; i++)
	{	
		size_t I = static_cast<size_t>(i);
		if(i-length >= 0)
			nodes[i]->addConnection(nodes[I-length], Direction::UP);
		if (i + length <= totalNodes - 1)
			nodes[i]->addConnection(nodes[I+length], Direction::DOWN);
		if(i-1 >= 0 && i%length != 0)
			nodes[i]->addConnection(nodes[I-1], Direction::LEFT);
		if (i + 1 <= totalNodes - 1 && (I - (static_cast<size_t>(length) - 1))%length != 0)
			nodes[i]->addConnection(nodes[I+1], Direction::RIGHT);	
	}

}

// Debugging function to print the grid graph
void Graph::printGrid(int length)
{
	int totalNodes = length * length;

	for (int i = 0; i < totalNodes - length + 1; i+=length) {
		// Format id(up, down, left, right, visited)
		for (int j = 0; j < length; j++) {
			size_t I = static_cast<size_t>(i);

			std::string up = nodes[I + j]->up ? std::to_string(*nodes[I + j]->up->id) : "x";
			std::string down = nodes[I + j]->down ? std::to_string(*nodes[I + j]->down->id) : "x";
			std::string left = nodes[I + j]->left ? std::to_string(*nodes[I + j]->left->id) : "x";
			std::string right = nodes[I + j]->right ? std::to_string(*nodes[I + j]->right->id) : "x";
			std::string visited = *nodes[I + j]->visited ? "Y" : "N";
			std::cout << *nodes[I + j]->id << "\t";/* << "("
			<< up << ","
			<< down << ","
			<< left << ","
			<< right << ","
			<< visited << ")"
			<< "  || ";*/
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
