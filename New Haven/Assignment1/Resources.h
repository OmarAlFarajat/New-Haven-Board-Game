#pragma once
#include <string>

using namespace std;
/*
TODO: implement draw() methods in HarvestDeck and BuildingDesk. Let's User use these methods
to draw a tiles (building or harvest)
*/

// The Deck of Harvest Tiles Object
class HarvestDeck 
{
public:
	HarvestDeck();
	HarvestTiles draw();

private:
	const static int numOfTiles = 60; // 60 Harvest Tiles
	static int numOfRemain;
	HarvestTiles deck[numOfTiles];

};

// The Deck of Building Object
class BuildingDeck 
{
public:
	BuildingDeck();
	BuildingTiles draw();

private:
	const static int numOfTiles = 144; // 144 buildings
	static int numOfRemain;
	BuildingTiles deck[numOfTiles];

};

// Harvest tiles Object
class HarvestTiles
{
public:
	HarvestTiles();
	bool isContain(ResourceType type);

private:
	const static int numOfResource = 4;
	Resource contain[numOfResource];

};

enum class BuildingType {MEADOW, QUARRY, FOREST, WHEATFIELD};
enum class BuildingColor {GREEN, GREY, RED, YELLOW};
// Building tiles Object
class BuildingTiles 
{
public:
	BuildingTiles();
	BuildingTiles(BuildingColor color, BuildingType buildingType, int value);
	BuildingType getBuildingType();

private:
	BuildingType *Type; 
	BuildingColor *Color; 
	int *Value;    // 1 to 6

};

enum class ResourceType { TIMBER, STONE, WHEAT, SHEEP};
class Resource
{
public:
	Resource();
	Resource(ResourceType type);

private:
	ResourceType *value;
};


// Hand Object 
class hand
{
public:
	hand();
	void exchange();

private:

};
