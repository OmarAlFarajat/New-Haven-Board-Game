#pragma once
#include <map>
#include <string>
#include <vector>

#include "GBMap.h"
#include "Building.h"
#include "Hand.h"
#include "Resources.h"
#include "VGMap.h"
#include "Player.h"

using std::string;
using std::cout;
using std::endl;

class Game : public Subject {

private:
	vector<Player*>* Players;
	GBMap* gb_map;
	HarvestDeck* harvestDeck;
	BuildingDeck* buildingDeck;
	Player* currentPlayer; 

public:
	Game(int number_of_players);
	~Game();

	void playerDrawHarvest(int player_index);

	void playerDrawBuilding(int player_index);

	void FillAvailableBuildings();
	GBMap* getGBMap();
	Player* getPlayer(int id);
	Player* getCurrentPlayer();
	void setCurrentPlayer(Player* playerIn);

	void PrintGameState();
};

// A3. >>> OBSERVED <<<
inline void Game::setCurrentPlayer(Player* playerIn) { 
	currentPlayer = playerIn; 
	// A3. Notify observers that player has changed.
	Notify("Player Change");
}
inline void Game::PrintGameState()
{
	for (int i = 0; i < Players[0].size(); i++) {
		int numberOfBuildingsMade = 0; 
		for (int j = 0; j < Players[0][i]->getVGMap()->getBuildingGraph()->getNumEnabledNodes(); j++)
			if (Players[0][i]->getVGMap()->getBuildingGraph()->getNode(j)->isOccupied())
				numberOfBuildingsMade++;
		cout << "\t\t\t$$$ "
			<< *Players[0][i]->getName() << ": "
			<< numberOfBuildingsMade << " buildings, "
			<< Players[0][i]->getVGMap()->calculatePoints() << " points.\n";
	}
}
inline GBMap* Game::getGBMap() { return gb_map; }
inline Player* Game::getPlayer(int id) { return Players[0][id];}
inline Player* Game::getCurrentPlayer() { return currentPlayer; }

// A3. Game Class Concrete Observer
class GameObserver : public Observer {
public:
	GameObserver(Game*);
	~GameObserver();
	void Update(Subject*,string);
	void Output(string);
private:
	Game* _subject;
};