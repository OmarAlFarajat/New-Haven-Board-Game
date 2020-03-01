#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

#include "VGMap.h"
#include "Resources.h"
#include "TileNode.h"

// TODO: Consider making all of this header-only? 
void loadVGMap(std::string& filename, VGMap& vg_map);

