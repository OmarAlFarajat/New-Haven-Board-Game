#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Node.h"
#include "Resources.h"

using std::vector;

class Graph
{
	vector<Node*>* nodes;
	int* numEnabledNodes;
	int* length;
	int* height;

public:
	Graph();
	~Graph();
	
	////	Initialization Functions

	/*	A helper function to the map loaders (VGMapLoader and BGMapLoader). 
	*	Length and height are read from the map files. 
	*	NodeType may either be TILE, RESOURCE, or BUILDING.	*/
	void makeGridGraph(int length, int height, NodeType nodeType);
	
	/*	A helper function to makeGridGraph(). 
	*	Will add a node to the member list of nodes.	*/
	void addNode(Node*);

	/*	This performs a linkage of GBMap's two Graph members: tileGraph and resourceGraphs.
	*	Each tile node will have a pointer to four resource nodes */
	void linkResourceNodes(Graph* graph);

	////	Debug

	/*	Prints the graph.
	*	When verbose is false, only the node ID is printed.
	*	When verbose is true, out and format will be: id(left, up, down, right)
	*	Can uncomment some code to also print if the node is visited/unvisited or enabled/disabled.*/
	void printGridGraph(bool verbose);

	/*	Returns true if the the graph is connected.
	*	Uses depthFirstSearch() recursively to determine connectivity.
	*	The node being passed is the starting node of choice.*/
	bool isConnected_DFS(Node*);

	/*	Used in GBMap.
	*	Will traverse the graph recursively using depthFirstSearch().
	*	It performs a DFS on condition that the connected node is the same ResourceType as the node being passed. 
	*(!)However, unlike isConnected_DFS, this does not reset the 'visited' state of the nodes.
	*	Used in GBMap::calcResourceAdjacencies() so that adjacent resources can be calculated for the resource tracker. */
	void DFS_ByType(Resource* node);

	/*	Helper function to DFS_ByType() and isConnected_DFS().
	*(!)Node's 'visited' member is mutated, i.e. not reset. Use resetAllVisited() to reset the visited states of all nodes.*/
	bool depthFirstSearch(Node*);
	
	// Setters
	void disableNode(int id);
	void enableNode(int id);
	void resetAllVisited();

	// Getters
	Node* getNode(int index);
	vector<Node*>* getNodes();
	int getNumEnabledNodes();
	int getLength();
	int getHeight();
};
inline Node* Graph::getNode(int index) { return nodes[0][index]; }
inline vector<Node*>* Graph::getNodes() { return nodes; }
inline int Graph::getNumEnabledNodes() { return *numEnabledNodes; }
inline int Graph::getLength() { return *length; }
inline int Graph::getHeight() { return *height; }
