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
	

public:

	vector<string>* VGMapsSelection; // a list of all the VGMap files as strings
	vector<Player*>* Players;
	GBMap* gameBoardMap;

	Game(int number_of_players);
	~Game();
		
};

