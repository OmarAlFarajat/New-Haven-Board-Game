#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "Node.h"

// Building tiles Object
enum class BuildingType { NONE, MEADOW, QUARRY, FOREST, WHEATFIELD };
enum class BuildingColor { NONE, GREEN, GREY, RED, YELLOW };
class BuildingTile : public Node
{
public:
	BuildingTile();
	BuildingTile(BuildingColor color, BuildingType buildingType, int value);
	~BuildingTile();
	BuildingType* getBuildingType();
	friend std::ostream& operator<<(std::ostream& os, BuildingTile& bt);
	std::string typeToString();
	std::string colorToString();
	int getValue() const { return *value; };

private:
	BuildingType* type; //opposite side type
	BuildingColor* color;
	int* value;    // 1 to 6

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

