#include "GBMapLoader.h"

ResourceType strToEnum(std::string str) {
	if (str.compare("SHEEP") == 0)
		return ResourceType::SHEEP;
	else if (str.compare("TIMBER") == 0)
		return ResourceType::TIMBER;
	else if (str.compare("STONE") == 0)
		return ResourceType::STONE;
	else if (str.compare("WHEAT") == 0)
		return ResourceType::WHEAT;
	else if (str.compare("NONE") == 0)
		return ResourceType::NONE;
}

void loadGBMap(std::string& fileName, GBMap& gb_map)
{
	std::ifstream inFile(fileName, std::ios::in);
	std::string lineRead;

	// The containers below store the data read from the file.
	// The graphs are only created and updated after the file is closed.
	int length = 0;
	int height = 0;
	std::map<int, std::vector<ResourceType>> resourceData;
	std::vector<int> resourceIndices; 
	std::vector<int> disableData;

	// Reading from file
	while (inFile) {

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
		else if (results[0].compare("LENGTH") == 0) 
			length = std::stoi(results[1]);
		else if (results[0].compare("HEIGHT") == 0) 
			height = std::stoi(results[1]);	
		else if (results[0].compare("RESOURCE") == 0){
			resourceData[std::stoi(results[1])] = { strToEnum(results[2]), strToEnum(results[3]), strToEnum(results[4]), strToEnum(results[5]) };
			resourceIndices.push_back(std::stoi(results[1]));
		}
		else if (results[0].compare("DISABLE") == 0) {
			disableData.push_back(std::stoi(results[1]));
		}
	}
	inFile.close();

	// Create the graphs using the length and height data from the file
	gb_map.getTileGraph()->makeGridGraph(length, height, NodeType::TILE);
	gb_map.getResourceGraph()->makeGridGraph(length * 2, height * 2, NodeType::RESOURCE);
	gb_map.getTileGraph()->linkResourceNodes(gb_map.getResourceGraph());

	// Iterate through the disableData and update gb_map's tile graph. 
	for (int i = 0; i < disableData.size(); i++)
		gb_map.getTileGraph()->disableNode(disableData[i]);

	// Iterate through the resourceData and update gb_map's tile graph. 
	for (int i = 0; i < resourceIndices.size(); i++) {
		static_cast<TileNode*>(gb_map.getTileGraph()->getNode(resourceIndices[i]))->getResourceNodes()[0]->setType(resourceData[resourceIndices[i]][0]);
		static_cast<TileNode*>(gb_map.getTileGraph()->getNode(resourceIndices[i]))->getResourceNodes()[1]->setType(resourceData[resourceIndices[i]][1]);
		static_cast<TileNode*>(gb_map.getTileGraph()->getNode(resourceIndices[i]))->getResourceNodes()[2]->setType(resourceData[resourceIndices[i]][2]);
		static_cast<TileNode*>(gb_map.getTileGraph()->getNode(resourceIndices[i]))->getResourceNodes()[3]->setType(resourceData[resourceIndices[i]][3]);
		gb_map.getTileGraph()->getNode(resourceIndices[i])->setOccupied(true);
	}
}

