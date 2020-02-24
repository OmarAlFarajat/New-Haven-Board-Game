#pragma once
#include <vector>
#include "GBMap.h"
#include "Harvest.h"
#include "Building.h"

// Hand Object 
class Hand 
{
	public:
	Hand();
	~Hand();
	int getRemainHarvest() {return *this->numOfHarvest;}
	bool hasNoHarvest() {return (*this->numOfHarvest == 0);}

	int getRemainBuilding() {return *this->numOfBuilding;}
	bool hasNoBuilding() { return (*this->numOfBuilding == 0);}

	HarvestTile* getHarvestTile(int index) {return this->harvestHold[0][index];}

	void showHand();
	void addHarvestTile(HarvestTile* ht);
	void addBuildingTile(BuildingTile* bt);
	int getNodeID(int row, int col);
	bool requestRotate(HarvestTile* target);
	void exchange(GBMap* gb_map, HarvestTile* target, TileNode*);
	int playHarvest(GBMap* gb_map);

private:
	int* numOfHarvest;
	int* numOfBuilding;
	std::vector<HarvestTile*>* harvestHold;
	std::vector<BuildingTile*>* buildingHold;

};


