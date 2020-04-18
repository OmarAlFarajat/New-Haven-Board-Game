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
	bool* isShipment; // shipment status
	bool* isBuilding;
	bool* isPond;

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
	void setOccupied(bool occupied);
	void setShipmentStatus(bool status);
	void setBuildingStatus(bool status);
	void setPondStatus(bool status);

	// Getters
	int getID();
	bool isVisited();
	bool isEnabled();
	bool isOccupied();
	Node* getUp();
	Node* getDown();
	Node* getLeft();
	Node* getRight();
	bool isShipmentTile();
	bool isBuildingTile();
	bool isPondTile();

	friend class Graph;
};

inline void Node::setOccupied(bool occupied) { *this->occupied = occupied; }
inline void Node::setShipmentStatus(bool status) { *isShipment = status;  }
inline void Node::setBuildingStatus(bool status) { *isBuilding = status; }
inline void Node::setPondStatus(bool status) { *isPond = status; }
inline int Node::getID() { return *id; }
inline bool Node::isVisited() { return *visited; }
inline bool Node::isEnabled() { return *enabled; }
inline bool Node::isOccupied() { return *occupied; }
inline Node* Node::getUp() { return up; }
inline Node* Node::getDown() { return down; }
inline Node* Node::getLeft() { return left; }
inline Node* Node::getRight() { return right; }
inline bool Node::isShipmentTile() { return *isShipment; }
inline bool Node::isBuildingTile() { return *isBuilding; }
inline bool Node::isPondTile() { return *isPond; }
