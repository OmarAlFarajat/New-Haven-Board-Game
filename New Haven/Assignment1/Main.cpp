#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "GBMap.h"
#include "Resources.h"
#include "Harvest.h"
#include "Building.h"
#include "Hand.h"
#include "Player.h"
#include "TileNode.h"
#include "VGMap.h"
#include "VGMapLoader.h"
#include "MapDrawer.h"
#include "Game.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

static Game* game;
static int numberOfPlayers;

void initialize() {
	// User prompted for number of players
	cout << "Please enter the number of players: " << endl;
	cin >> numberOfPlayers; 
	game = new Game(numberOfPlayers);
}

void testGame() {

	MapDrawer drawer;

	// CIMG Window Draw Loop
	while (true)
	{
		for (int i = 0; i < numberOfPlayers; i++) {

			main_disp = cimg_library::CImgDisplay(drawer.drawGame(*game->getGBMap(), *game->getPlayer(i)), "New Haven");
			main_disp.move(main_disp_x, main_disp_y);

			game->getPlayer(i)->PlaceShipmentTile(game->getGBMap());
			main_disp = cimg_library::CImgDisplay(drawer.drawGame(*game->getGBMap(), *game->getPlayer(i)), "New Haven");
			main_disp.move(main_disp_x, main_disp_y);

			//game->getPlayer(i)->show();

			main_disp = cimg_library::CImgDisplay(drawer.drawGame(*game->getGBMap(), *game->getPlayer(i)), "New Haven");
			main_disp.move(main_disp_x, main_disp_y);

			game->getPlayer(i)->PlaceHarvestTile(game->getGBMap());
			main_disp = cimg_library::CImgDisplay(drawer.drawGame(*game->getGBMap(), *game->getPlayer(i)), "New Haven");
			main_disp.move(main_disp_x, main_disp_y);

			game->getPlayer(i)->PlaceBuildingTile(game->getPlayer(i)->getVGMap());
			//game->getPlayer(i)->show();
			main_disp = cimg_library::CImgDisplay(drawer.drawGame(*game->getGBMap(), *game->getPlayer(i)), "New Haven");
			main_disp.move(main_disp_x, main_disp_y);

			cout << "Number of points from VGMap " << game->getPlayer(0)->getVGMap()->calculatePoints() << endl;

			cout << "Shipment Tile flipped!" << endl; 
			game->getPlayer(i)->UncoverShipment(game->getGBMap());
			main_disp = cimg_library::CImgDisplay(drawer.drawGame(*game->getGBMap(), *game->getPlayer(i)), "New Haven");
			main_disp.move(main_disp_x, main_disp_y);

			cout << "END OF " << *game->getPlayer(i)->getName() << "'s turn!" << endl;
			system("Pause");
		}

	main_disp.wait();

	}

}

int main() {
	srand(time(nullptr));

	initialize();
	testGame();

	return 0;
}
