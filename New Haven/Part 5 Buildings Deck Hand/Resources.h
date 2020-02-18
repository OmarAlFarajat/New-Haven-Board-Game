#pragma once

/*
TODO: implement draw() methods in HarvestDeck and BuildingDesk. Let's User use these methods
to draw a tiles (building or harvest)
*/


// Resource Class
enum class ResourceType { TIMBER, STONE, WHEAT, SHEEP};
class Resource
{
public:
	Resource();
	Resource(ResourceType type);
	~Resource();

private:
	ResourceType* value;
};

// Harvest tiles Object
class HarvestTiles
{
public:
	HarvestTiles();
	~HarvestTiles();
	bool isContain(ResourceType type);

private:
	const static int numOfResource = 4;
	Resource contain[numOfResource];

};


// The Deck of Harvest Tiles Object
class HarvestDeck 
{
public:
	HarvestDeck();
	~HarvestDeck();
	HarvestTiles draw();

private:
	const static int numOfTiles = 60; // 60 Harvest Tiles
	static int numOfRemain;
	static HarvestTiles deck[numOfTiles];

};


// Building tiles Object
enum class BuildingType {MEADOW, QUARRY, FOREST, WHEATFIELD};
enum class BuildingColor {GREEN, GREY, RED, YELLOW};
class BuildingTile 
{
public:
	BuildingTile();
	BuildingTile(BuildingColor color, BuildingType buildingType, int value);
	~BuildingTile();
	BuildingType getBuildingType();

private:
	BuildingType* type; 
	BuildingColor* color; 
	int *value;    // 1 to 6

};


// The Deck of Building Object
class BuildingDeck 
{
public:
	BuildingDeck();
	~BuildingDeck();
	BuildingTile draw();

private:
	const static int numOfTiles = 144; // 144 buildings
	static int numOfRemain;
	BuildingTile deck[numOfTiles];

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
