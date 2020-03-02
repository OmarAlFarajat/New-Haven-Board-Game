#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <map>

#include "GBMap.h"
#include "Resources.h"
#include "TileNode.h"

// TODO: Consider making all of this header-only?  
void loadGBMap(std::string& filename, GBMap& gb_map);

