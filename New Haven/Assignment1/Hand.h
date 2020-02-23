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
	bool hasNoHarvest() {return (*this->remainHarvest == 0);}
	int getRemainHarvest() {return *this->remainHarvest;}
	int getRemainBuilding() {return *this->remainBuilding;}
	HarvestTile* getHarvestTile(int index) {return this->harvestHold[0][index];}
	void rotateRequest(HarvestTile* target);
	void exchange(GBMap* gb_map);
	int playHarvest(GBMap* gb_map);

private:
	int* remainHarvest;
	int* remainBuilding;
	std::vector<HarvestTile*>* harvestHold;
	std::vector<BuildingTile*>* buildingHold;

};


