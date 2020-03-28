#include <iostream>
#include "Game.h"
#include "VGMap.h"
#include "Player.h"

using std::cout;
using std::endl;
using std::endl;
using std::string;

Game::Game(int number_of_players)
{
	/*	TODO
	*	Selects a VGMap randomly from VGMapsSelectionand sets that selection to a newly instantiated VGMap attached to each
	*	Player object(remember to pop the selected VGMap out of the listand set the bounds of your random selection to adjust
	*	based on the size after popping the used elements out).*/
	vector<string>* VGMapsSelection;
	
	// vector of strings or vector of VGMap objects?
	//vector<VGMap>* VGMapSelector;

	//Create Player objects and store them in Players vector
	vector<Player*>* Players;

	//Switch statement instantiates gameBoardMap using the appropriate map file depending on # of players.
	GBMap* gameBoardMap = new GBMap();
}

Game::~Game()
{
	VGMapsSelection = nullptr;
	Players = nullptr;
	gameBoardMap = nullptr;

	delete VGMapsSelection;
	delete Players;
	delete gameBoardMap;
}