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

public:
	Game(int number_of_players);
	~Game();

	GBMap* getGBMap();
	Player* getPlayer(int id);
};
inline GBMap* Game::getGBMap() { return gb_map; }
inline Player* Game::getPlayer(int id) { return Players[0][id];}
