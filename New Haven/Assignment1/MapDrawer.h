#pragma once
#include "GBMap.h"
#include "CImg.h"
using namespace cimg_library;

CImg<unsigned char> ResourceToBMP(ResourceType type);
void drawGBMap(GBMap& gb_map);

