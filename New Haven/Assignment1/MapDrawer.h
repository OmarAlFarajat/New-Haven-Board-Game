#pragma once
#include "GBMap.h"
#include "CImg.h"
#include "Player.h"

using namespace cimg_library;

CImg<unsigned char> ResourceToBMP(ResourceType type);
CImg<unsigned char> drawGame(GBMap& gb_map, Player& player);

