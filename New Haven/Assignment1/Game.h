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


class Game {

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
};
inline void Game::setCurrentPlayer(Player* playerIn) { currentPlayer = playerIn; }
inline GBMap* Game::getGBMap() { return gb_map; }
inline Player* Game::getPlayer(int id) { return Players[0][id];}
inline Player* Game::getCurrentPlayer() { return currentPlayer; }
