#include "VGMapLoader.h"
#include <cctype>
#include <map>

ResourceType resourceStringToType(std::string str)
{

	if (str.compare("SHEEP") == 0)
		return ResourceType::SHEEP;

	if (str.compare("STONE") == 0)
		return ResourceType::STONE;

	if (str.compare("TIMBER") == 0)
		return ResourceType::TIMBER;

	if (str.compare("WHEAT") == 0)
		return ResourceType::WHEAT;
}

void loadVGMap(std::string& fileName, VGMap& vg_map) {
	std::ifstream inFile(fileName, std::ios::in);
	std::string lineRead;

	// The containers below store the data read from the file.
	// The graphs are only created and updated after the file is closed. 
	std::string name = "";
	int length = 0;
	int height = 0;
	std::vector<int> disableData;

	struct buildingData {
		ResourceType type;
		int value;
		bool faceUp;
	};

	std::map<int, buildingData> buildingContainer; 

	while (inFile) {

		// Read the next line and store in lineRead for parsing
		getline(inFile, lineRead);

		// Checking for whitespace and empty strings to skip. 
		bool whiteSpaced = true;
		for (int i = 0; i < lineRead.length(); i++) 
			if (!isspace(lineRead.at(i))) {
				whiteSpaced = false;
				break;
			}
		
		if (lineRead.empty() || whiteSpaced)
			continue;

		// String tokenizing code used for parsing the loaded map file 
		// Source: https://stackoverflow.com/a/53921
		std::stringstream strstr(lineRead);
		std::istream_iterator<std::string> it(strstr);
		std::istream_iterator<std::string> end;
		std::vector<std::string> results(it, end);

		if (results[0].compare("#") == 0)
			continue;
		else if (results[0].compare("NAME") == 0)
			name = results[1];
		else if (results[0].compare("LENGTH") == 0)
			length = std::stoi(results[1]);
		else if (results[0].compare("HEIGHT") == 0)
			height = std::stoi(results[1]);
		else if (results[0].compare("DISABLE") == 0) {
			disableData.push_back(std::stoi(results[1]));
		}else if (results[0].compare("BUILDING") == 0) {
			buildingContainer[std::stoi(results[1])].type = resourceStringToType(results[2]); 
			buildingContainer[std::stoi(results[1])].value = std::stoi(results[3]);
            buildingContainer[std::stoi(results[1])].faceUp = results[4].compare("UP") == 0;

		}

	}
	inFile.close();

	vg_map.getBuildingGraph()->makeGridGraph(length, height, NodeType::BUILDING);

	vg_map.initTileValues();

	// Iterate through the disableData and update gb_map's tile graph. 
	for (int i = 0; i < disableData.size(); i++)
		vg_map.getBuildingGraph()->disableNode(disableData[i]);

	std::map<int, buildingData>::iterator it;

	for (it = buildingContainer.begin(); it != buildingContainer.end(); it++)
	{
		static_cast<BuildingTile*>(vg_map.getBuildingGraph()->getNode(it->first))->setType(it->second.type);
		static_cast<BuildingTile*>(vg_map.getBuildingGraph()->getNode(it->first))->setValue(it->second.value);
		static_cast<BuildingTile*>(vg_map.getBuildingGraph()->getNode(it->first))->setFaceUp(it->second.faceUp);
		static_cast<BuildingTile*>(vg_map.getBuildingGraph()->getNode(it->first))->setOccupied(true);
	}
}
