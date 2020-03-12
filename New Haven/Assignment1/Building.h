#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "Node.h"
#include "Resources.h"

class BuildingTile : public Node
{
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

public:
	BuildingTile();
	BuildingTile(ResourceType type, int value);
	~BuildingTile();

	friend std::ostream& operator<<(std::ostream& os, BuildingTile& bt);
	std::string typeToString();

	ResourceType* getBuildingTypePointer();
	int getValue() const;
	ResourceType getType() const;
	bool isFaceUp() const;
	void setValue(int value);
	void setType(ResourceType type);
	void setFaceUp(bool faceUp);

};

inline ResourceType* BuildingTile::getBuildingTypePointer() { return type; }
inline int BuildingTile::getValue() const { return *value; };
inline ResourceType BuildingTile::getType() const { return *type; };
inline bool BuildingTile::isFaceUp() const { return *faceUp; };
inline void BuildingTile::setValue(int value) { *this->value = value; }
inline void BuildingTile::setType(ResourceType type) { *this->type = type;  }
inline void BuildingTile::setFaceUp(bool faceUp) { *this->faceUp = faceUp; }

// The Deck of Building Object
class BuildingDeck
{
	const static int numOfTiles = 144; // 144 buildings
	int* tileIndex;
	std::vector<BuildingTile> deck;

public:
	BuildingDeck();
	~BuildingDeck();
	BuildingTile* draw();
	int getNumOfRemain() const;
};
inline int BuildingDeck::getNumOfRemain() const { return *this->tileIndex;  };
