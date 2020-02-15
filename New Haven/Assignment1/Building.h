#pragma once
#include "Resources.h"

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

