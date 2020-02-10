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
//	HarvestTiles draw();

private:
	int NumOfObj;

};

// The Deck of Building Object
class BuildingDeck 
{
public:
	BuildingDeck();
//	BuildingTiles draw();

private:

};

// Harvest tiles Object
class HarvestTiles
{
public:
	HarvestTiles();

private:
	const static int numOfResource = 4;
	Resources contain[numOfResource];

};

// Building tiles Object
class BuildingTiles 
{
public:
	BuildingTiles();

private:
	string title; // meadow, quarry, forest, wheatfield
	string color; // green, grey, red, yellow
	int value;    // 1 to 6

};

// Hand Object 
class hand
{
public:
	hand();
	void exchange();

private:

};

class Resources
{
public:
	Resources();
	Resources(string value);
	bool isValidValue(string value);

private:
	string value; //wood, silver, wheat
	string valid_values[3] = { "wood", "silver", "wheat" };

};


