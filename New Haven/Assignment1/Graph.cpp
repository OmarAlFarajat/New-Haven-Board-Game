#include <iomanip>
#include "Graph.h"
#include "Resources.h"
#include "TileNode.h"
#include "Building.h"

// Template for evenly spacing out elements of a table (or a grid in this case)
// To be used in makeGridGraph()
// Source: https://stackoverflow.com/a/14796892
template<typename T> void printElement(T t, const int& width)
{
	std::cout << std::left << std::setw(width) << std::setfill(' ') << t;
}

Graph::Graph()
{
	length = new int(0);
	height = new int(0);
	numEnabledNodes = new int(0);
	nodes = new std::vector<Node*>;
}

Graph::~Graph()
{
}

// A recursive depth-first search that visits all nodes from the passed root node to check if the graph is connected
bool Graph::isConnected_DFS(Node* node)
{
	bool isConnected = depthFirstSearch(node);
	resetAllVisited();

	return isConnected; 
}

bool Graph::depthFirstSearch(Node* node) {
	// Mark the node as visited
	*node->visited = true;
	// Recursive calls
	// If connection is not null AND the connected node has not been visited AND the connected node is enabled
	if (node->up && !*node->up->visited && *node->up->enabled)
		depthFirstSearch(node->up);

	if (node->down && !*node->down->visited && *node->down->enabled)
		depthFirstSearch(node->down);

	if (node->left && !*node->left->visited && *node->left->enabled)
		depthFirstSearch(node->left);

	if (node->right && !*node->right->visited && *node->right->enabled)
		depthFirstSearch(node->right);

	// Count how many nodes have been visited
	int counter = 0;
	for (int i = 0; i < nodes[0].size(); i++)
		if (*nodes[0][i]->visited)
			counter++;

	// Compare it with the total number of nodes. 
	// If number of nodes visisted is equal to total number of nodes, then graph is connected.  
	if (counter == *numEnabledNodes)
		return true;
	else
		return false;
}

void Graph::DFS_ByType(Resource* node) {
	// Mark the node as visited
	*node->visited = true;
	// Recursive calls
	// If connection is not null AND the connected node has not been visited AND the connected node is enabled AND the connected node is the same Resource type
	if (node->up && !*node->up->visited && *node->up->enabled && (static_cast<Resource*>(node->up)->getType() == node->getType()))
		DFS_ByType(static_cast<Resource*>(node->up));

	if (node->down && !*node->down->visited && *node->down->enabled && (static_cast<Resource*>(node->down)->getType() == node->getType()))
		DFS_ByType(static_cast<Resource*>(node->down));

	if (node->left && !*node->left->visited && *node->left->enabled && (static_cast<Resource*>(node->left)->getType() == node->getType()))
		DFS_ByType(static_cast<Resource*>(node->left));

	if (node->right && !*node->right->visited && *node->right->enabled && (static_cast<Resource*>(node->right)->getType() == node->getType()))
		DFS_ByType(static_cast<Resource*>(node->right));
}

void Graph::resetAllVisited()
{
	for (int i = 0; i < nodes[0].size(); i++) 
		*nodes[0][i]->visited = false;
}

void Graph::disableNode(int id)
{
	if (*this->getNode(id)->enabled) {
		*this->getNode(id)->enabled = false;
		(*numEnabledNodes)--;
	}
}

void Graph::enableNode(int id)
{
	if (!(*this->getNode(id)->enabled)) {
		*this->getNode(id)->enabled = true;
		(*numEnabledNodes)++;
	}
}

void Graph::addNode(Node* node)
{
	*node->id = *numEnabledNodes;
	(*numEnabledNodes)++;
	nodes[0].push_back(node);
}

// Links the appropriate tile nodes to the corresponding resource nodes (part of map initiation)
void Graph::linkResourceNodes(Graph* resourceGraph)
{
	int totalNodes = *this->length * *this->height;
	int rowCount = 0;
	int rowValue = 0; 

	for (int i = 0; i < totalNodes; i++)
	{
		// rowCount is used to keep track of which row node i is in
		// The row value is used in the calculations to figure out the mapping of the resource id to a tile id. 
		if (rowCount == *this->length) {
			rowCount = 0; 
			rowValue++;
		}

		// Resources on Harvest tile: 
		//	|0|1|
		//	|3|2|
		// Calculate the first Resource id number based on the Tile 
		int firstResource = (i * 2) + (*this->length*rowValue*2);

		// Link the nodes in the Resource graph to the nodes in the Tile graph based on calculations 
		static_cast<TileNode*>(nodes[0][i])
			->linkResourceNode(static_cast<Resource*>(resourceGraph->getNode(firstResource)), 0);
		static_cast<TileNode*>(nodes[0][i])
			->linkResourceNode(static_cast<Resource*>(resourceGraph->getNode(firstResource + 1)), 1);
		static_cast<TileNode*>(nodes[0][i])
			->linkResourceNode(static_cast<Resource*>(resourceGraph->getNode(firstResource + *this->length * 2)), 2);
		static_cast<TileNode*>(nodes[0][i])
			->linkResourceNode(static_cast<Resource*>(resourceGraph->getNode(firstResource + *this->length * 2 + 1)), 3);

		rowCount++; 
	}
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
		case NodeType::BUILDING:
			this->addNode(new BuildingTile());
			break;
		}
	}

	// Create all the edges
	for (int i = 0; i < totalNodes; i++)
	{
		size_t I = static_cast<size_t>(i);
		// Calculations based on the node id are used to ensure connections form a grid-shaped graph. 
		if (i - length >= 0)
			nodes[0][i]->addEdge(nodes[0][I - length], Direction::UP);
		if (i + length <= totalNodes - 1)
			nodes[0][i]->addEdge(nodes[0][I + length], Direction::DOWN);
		if (i - 1 >= 0 && i % length != 0)
			nodes[0][i]->addEdge(nodes[0][I - 1], Direction::LEFT);
		if (i + 1 <= totalNodes - 1 && (I - (static_cast<size_t>(length) - 1)) % length != 0 || i == 3)			
			nodes[0][i]->addEdge(nodes[0][I + 1], Direction::RIGHT);
	}

	*this->length = length;
	*this->height = height;
}

// Debugging function to print the grid graph
void Graph::printGridGraph(bool verbose)
{
	int totalNodes = *this->length * *this->height;

	for (int i = 0; i < totalNodes - *this->length + 1; i += *this->length) {
		// Format id(left, up, down, right, visited, enabled)
		for (int j = 0; j < *this->length; j++) {
			size_t I = static_cast<size_t>(i);

			/*	If connected node isn't null AND if current node is enabled AND if connected node is enabled.
			*	Take note of the conditional ? operator, it might not be clear in the block of code below. 
			*	Will print each node's connected nodes if verbose is enabled.
			*	If no connection exists, then an 'x' is put in place.
			*	Prints if the node has been visited and enabled. */
			std::string up = (nodes[0][I + j]->up && *nodes[0][I + j]->enabled && *nodes[0][I + j]->up->enabled) ? std::to_string(*nodes[0][I + j]->up->id) : "x";
			std::string down = (nodes[0][I + j]->down && *nodes[0][I + j]->enabled && *nodes[0][I + j]->down->enabled) ? std::to_string(*nodes[0][I + j]->down->id) : "x";
			std::string left = (nodes[0][I + j]->left && *nodes[0][I + j]->enabled && *nodes[0][I + j]->left->enabled) ? std::to_string(*nodes[0][I + j]->left->id) : "x";
			std::string right = (nodes[0][I + j]->right && *nodes[0][I + j]->enabled && *nodes[0][I + j]->right->enabled) ? std::to_string(*nodes[0][I + j]->right->id) : "x";
			std::string visited = *nodes[0][I + j]->visited ? "Y" : "N";
			std::string enabled = *nodes[0][I + j]->enabled ? "Y" : "N";
			std::string temp = "";

			// Print more information per node is verbose is enabled.
			if (verbose) {
				temp = std::to_string(*nodes[0][I + j]->id) + " ("
					+ left + ","
					+ up + ","
					+ down + ","
					+ right /*+ ","
					+ visited + ","
					+ enabled*/ + ")";
				printElement(temp, 23);
			}
			else {
				temp = std::to_string(*nodes[0][I + j]->id) + "";
				printElement(temp, 5);
			}


		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}