#include "Graph.h"
#include "Resources.h"
#include "TileNode.h"

Graph::Graph()
{
	length = new int(0);
	height = new int(0);
	number_of_nodes = new int(0);
	nodes = new std::vector<Node*>;
}

Graph::~Graph()
{
}

// A recursive depth-first search
bool Graph::isConnected_DFS(Node* node)
{
	// Mark the node as visited
	*node->visited = true;

	// Recursive calls
	// If connection is not null and the connected node has not been visited 
	if (node->up && !*node->up->visited && *node->up->enabled)
		isConnected_DFS(node->up);

	if (node->down && !*node->down->visited && *node->down->enabled)
		isConnected_DFS(node->down);

	if (node->left && !*node->left->visited && *node->left->enabled)
		isConnected_DFS(node->left);

	if (node->right && !*node->right->visited && *node->right->enabled)
		isConnected_DFS(node->right);

	// Count how many nodes have been visited
	int counter = 0;
	for (int i = 0; i < nodes[0].size(); i++)
		if (*nodes[0][i]->visited)
			counter++;

	// Compare it with the total number of nodes. 
	// If number of nodes visisted is equal to total number of nodes, then graph is connected.  
	if (counter == *number_of_nodes) 
		return true;
	else
		return false;

}

void Graph::disableNode(int id)
{
	if (*this->getNode(id)->enabled) {
		*this->getNode(id)->enabled = false;
		(*number_of_nodes)--;
	}
}

void Graph::enableNode(int id)
{
	if (!(*this->getNode(id)->enabled)) {
		*this->getNode(id)->enabled = true;
		(*number_of_nodes)++;
	}
}

void Graph::resetAllVisited()
{
	for (int i = 0; i < nodes->size(); i++) {
		*nodes[0][i]->visited = false;
	}

}

void Graph::addNode(Node* node)
{
	*node->id = *number_of_nodes;
	(*number_of_nodes)++;
	nodes[0].push_back(node);
}

// Makes a square grid of size length x length. 
void Graph::makeGridGraph(int length, int height, NodeType nodeType)
{
	// First create all the nodes
	int totalNodes = length * height;
	for (int i = 0; i < totalNodes; i++) {
		switch (nodeType) {
		case NodeType::RESOURCE:
			this->addNode(new Resource());
			break;
		case NodeType::TILE:
			this->addNode(new TileNode());
			break;
		}
	}

	// Create all the edges
	for (int i = 0; i < totalNodes; i++)
	{
		size_t I = static_cast<size_t>(i);
		// If-conditions ensure that the edges are made to form a grid
		if (i - length >= 0)
			nodes[0][i]->addEdge(nodes[0][I - length], Direction::UP);
		if (i + length <= totalNodes - 1)
			nodes[0][i]->addEdge(nodes[0][I + length], Direction::DOWN);
		if (i - 1 >= 0 && i % length != 0)
			nodes[0][i]->addEdge(nodes[0][I - 1], Direction::LEFT);
		if (i + 1 <= totalNodes - 1 && (I - (static_cast<size_t>(length) - 1)) % length != 0)
			nodes[0][i]->addEdge(nodes[0][I + 1], Direction::RIGHT);
	}

	*this->length = length;
	*this->height = height;
}

// Debugging function to print the grid graph
void Graph::printGridGraph(bool verbose)
{
	for (int i = 0; i < *number_of_nodes - *this->length + 1; i += *this->length) {
		// Format id(up, down, left, right, visited)
		for (int j = 0; j < *this->length; j++) {
			size_t I = static_cast<size_t>(i);

			std::string up = (nodes[0][I + j]->up && *nodes[0][I + j]->enabled && *nodes[0][I + j]->up->enabled) ? std::to_string(*nodes[0][I + j]->up->id) : "x";
			std::string down = (nodes[0][I + j]->down && *nodes[0][I + j]->enabled && *nodes[0][I + j]->down->enabled) ? std::to_string(*nodes[0][I + j]->down->id) : "x";
			std::string left = (nodes[0][I + j]->left && *nodes[0][I + j]->enabled && *nodes[0][I + j]->left->enabled) ? std::to_string(*nodes[0][I + j]->left->id) : "x";
			std::string right = (nodes[0][I + j]->right && *nodes[0][I + j]->enabled && *nodes[0][I + j]->right->enabled) ? std::to_string(*nodes[0][I + j]->right->id) : "x";
			std::string visited = *nodes[0][I + j]->visited ? "Y" : "N";
			std::string enabled = *nodes[0][I + j]->enabled ? "Y" : "N";

			std::cout << *nodes[0][I + j]->id << " ";
			// Print more information per node is verbose is enabled.
			if (verbose)
				std::cout << "("
				<< up << ","
				<< right << ","
				<< down << ","
				<< left << ","
				<< visited << ","
				<< enabled << ")"
				<< "  || ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}