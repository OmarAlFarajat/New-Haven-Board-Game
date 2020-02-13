#pragma once
#include "GBMap.h"

/*
TODO: implement draw() methods in HarvestDeck and BuildingDesk. Let's User use these methods
to draw a tiles (building or harvest)
*/

// Resource class (extends Node)
enum class ResourceType { TIMBER, STONE, WHEAT, SHEEP };
class Resource : public Node
{
public:
	Resource();
	~Resource();
	void setType(ResourceType type);
private:
	ResourceType* type;
};

// Harvest tile class (extends Node)
class HarvestTile : public Node
{
public:
	HarvestTile();
	HarvestTile(Resource[4]);
	~HarvestTile();

private:
	Resource* resources[4];
};

/////////////
// TO-DO ... 
//
// The Deck of Harvest Tiles Object
class HarvestDeck
{
public:
	HarvestDeck();
	~HarvestDeck();
	HarvestTile draw();

private:
	const static int numOfTiles = 60; // 60 Harvest Tiles
	static int numOfRemain;
	static HarvestTile deck[numOfTiles];

};

// Building tiles Object
enum class BuildingType { MEADOW, QUARRY, FOREST, WHEATFIELD };
enum class BuildingColor { GREEN, GREY, RED, YELLOW };
class BuildingTiles
{
public:
	BuildingTiles();
	BuildingTiles(BuildingColor color, BuildingType buildingType, int value);
	~BuildingTiles();
	BuildingType getBuildingType();

private:
	BuildingType* Type;
	BuildingColor* Color;
	int* Value;    // 1 to 6

};

// The Deck of Building Object
class BuildingDeck
{
public:
	BuildingDeck();
	~BuildingDeck();
	BuildingTiles draw();

private:
	const static int numOfTiles = 144; // 144 buildings
	static int numOfRemain;
	BuildingTiles deck[numOfTiles];

};

// Hand Object 
class hand
{
public:
	hand();
	~hand();
	void exchange();

private:

};
