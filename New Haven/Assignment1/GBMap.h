#pragma once
#include <vector>
#include <map>


#include "Graph.h"
#include "TileNode.h"
#include "Harvest.h"
#include "Building.h"
#include "GameObservers.h"

class GBMap : public Subject
{
	Graph* tileGraph;								// The tiles on the gameboard itself. Composed of 'TileNodes'.
	Graph* resourceGraph;							// A graph representing all the resources that can be on the board. Composed of 'Resource' nodes. 
	std::map<ResourceType, int>* resourceTracker;	// Keeps track of the number of resources accumulated from Harvset tile placement
	BuildingTile* buildingsAvailable[5];			// TODO: A container for the 5 buildings that should be out on the gameboard. 

public:
	GBMap();
	~GBMap();

	bool GameOver(); 
	
	/*	Uses HarvestTile information to set the Resource nodes linked to TileNode. 
	*	Sets TileNode to occupied. 
	*(!)This function behaves like a setter. 
	*(!)It's intended use is only as a helper for Hand::playHarvest() in conjunction with isValid().	*/
	bool placeHarvestTile(HarvestTile* harvestTile, TileNode* tileNode);

	BuildingTile* DrawBuilding(BuildingDeck* deck);

	/*	A helper function for Hand::playHarvest().
	*	Ensures that the request to place a Harvest tile on the board is valid.	*/
	bool isValid(TileNode* tileNode);

	/*	Prints the values of each ResourceType held in resourceTracker */
	void displayResourceTracker();

	/*	Used when a Harvest tile is placed on the board. 
	*	Performs DFS for each Resource node linked with the passed TileNode.
	*	Counts up the visited nodes for each ResourceType and passes it back through output as a map.	*/
	void calcResourceAdjacencies(TileNode* root, std::map<ResourceType, int>& output);

	// Resource Tracker operations
	// A3. >>> OBSERVED <<<
	void setResourceTracker(std::map<ResourceType, int>* inTracker);
	// A3. >>> OBSERVED <<<
	void spendResource(ResourceType, int);
	bool isValidExpense(ResourceType, int);
	bool hasWealthToShare();

	//void setAvailableBuilding(int index, BuildingTile* building);
  
	// Getters
	Graph* getTileGraph();
	Graph* getResourceGraph();
	std::map<ResourceType, int>* getResourceTracker();
	BuildingTile* getBuildingsAvailable();

	friend class Game;
	friend class MapDrawer;
};
inline Graph* GBMap::getTileGraph() { return tileGraph; }
inline Graph* GBMap::getResourceGraph() { return resourceGraph; }
inline std::map<ResourceType, int>* GBMap::getResourceTracker() { return resourceTracker; }
inline BuildingTile* GBMap::getBuildingsAvailable() { return buildingsAvailable[0]; }
//inline void GBMap::setAvailableBuilding(int index, BuildingTile* building) { *buildingsAvailable[0] = *building; }
//inline BuildingTile GBMap::getAvailableBuilding(int index) { return *buildingsAvailable[index]; }

// A3. GBMap Class Concrete Observer
class GBMapObserver : public Observer {
public:
	GBMapObserver(GBMap*);
	~GBMapObserver();
	void Update(Subject*,string);
	void Output(string);
private:
	GBMap* _subject;
};
