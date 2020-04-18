#include "Node.h"
#include "Graph.h"

Node::Node()
{
	id = new int(-1);
	visited = new bool(false);
	enabled = new bool(true); 
	occupied = new bool(false);
	up = NULL;
	down = NULL;
	right = NULL;
	left = NULL;
	isShipment = new bool(false);
	isBuilding = new bool(false);
	isPond = new bool(false);
}

Node::~Node()
{
	// TODO: Causes errors
	id = nullptr;
	visited = nullptr;
	enabled = nullptr;
	occupied = nullptr;

	delete id;
	delete visited;
	delete enabled;
	delete occupied;

	//delete up;
	//delete down;
	//delete left;
	//delete right;
}

void Node::addEdge(Node* node, Direction direction)
{
	switch (direction) {
	case Direction::UP:
		up = node;
		break;
	case Direction::DOWN:
		down = node;
		break;
	case Direction::RIGHT:
		right = node;
		break;
	case Direction::LEFT:
		left = node;
		break;
	}
}
