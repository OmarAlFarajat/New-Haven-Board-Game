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

using std::string;

// TODO: Consider making all of this header-only?  
void loadGBMap(string& filename, GBMap& gb_map);

