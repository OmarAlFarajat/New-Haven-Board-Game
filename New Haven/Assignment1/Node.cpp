#include "Node.h"

Node::Node()
{
	id = new int(-1);
	visited = new bool(false);
	up = NULL;
	down = NULL;
	right = NULL;
	left = NULL;
}

Node::~Node()
{
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
