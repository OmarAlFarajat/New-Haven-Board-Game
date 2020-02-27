#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "Node.h"
#include "Resources.h"

class BuildingTile : public Node
{
public:
	BuildingTile();
	BuildingTile(ResourceType type, int value);
	~BuildingTile();
	ResourceType* getBuildingType();
	friend std::ostream& operator<<(std::ostream& os, BuildingTile& bt);
	std::string typeToString();
	int getValue() const { return *value; };

private:
	ResourceType* type; //opposite side type
	int* value;    // 1 to 6
	bool* faceUp; 

};

// The Deck of Building Object
class BuildingDeck
{
public:
	BuildingDeck();
	~BuildingDeck();
	BuildingTile* draw();
	int getNumOfRemain() const { return *this->tileIndex;  };

private:
	const static int numOfTiles = 144; // 144 buildings
	int* tileIndex;
	std::vector<BuildingTile> deck;

};

