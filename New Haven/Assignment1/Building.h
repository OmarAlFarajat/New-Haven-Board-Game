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
	// Inline getters
	int getValue() const { return *value; };
	ResourceType getType() const { return *type; };
	bool getFaceUp() const { return *faceUp; };
	void setValue(int value) { *this->value = value; }
	void setType(ResourceType type) { *this->type = type;  }
	void setFaceUp(bool faceUp) { *this->faceUp = faceUp; }
private:
	/*
	NOTE:
	The team decided to have an attribute "type" is of ResourceType
	=> Indicating which ResourceType built the building instead of having Color
	"faceUp" is an attribute of boolean type which shows whether or not the tile is facing up (with value) 
	or facing down (player only needs 1 resource to build)

	The team also decided to remove the BuildingType as it is unused/unimportant in any part of the game
	*/
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

