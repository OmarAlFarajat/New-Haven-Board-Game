#pragma once
#include <map>
#include <vector>
#include "GBMap.h"
#include "Harvest.h"
#include "Building.h"
#include "VGMap.h"

// Hand Object 
class Hand 
{
	public:
	Hand();
	~Hand();
	//Inline getters
	int getRemainHarvest() {return *this->numOfHarvest;}
	int getRemainBuilding() {return *this->numOfBuilding;}
	bool hasNoHarvest() {return (*this->numOfHarvest == 0);}
	bool hasNoBuilding() { return (*this->numOfBuilding == 0);}

	HarvestTile* getHarvestTile(int index) {return this->harvestHold[0][index];}
	BuildingTile* getBuildingTile(int index) { return this->buildingHold[0][index]; }

	void showHand();
	void addHarvestTile(HarvestTile* ht);
	void addBuildingTile(BuildingTile* bt);
	int getNodeID(GBMap* gb_map, int row, int col);
	int getNodeID_VG(VGMap* vg_map, int row, int col);

    void exchange(GBMap* gb_map, TileNode*);
	bool requestRotate(HarvestTile* target);
	int playHarvest(GBMap* gb_map);

	bool requestFlip(BuildingTile* target);
	void playBuilding(VGMap* vg_map);
private:
	int* numOfHarvest;
	int* numOfBuilding;
	std::vector<HarvestTile*>* harvestHold;
	std::vector<BuildingTile*>* buildingHold;
};


