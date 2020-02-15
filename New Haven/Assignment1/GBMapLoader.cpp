#include "GBMapLoader.h"

void loadMap(std::string& fileName, GBMap& gb_map)
{
	std::ifstream inFile(fileName, std::ios::in);
	std::string lineRead;
	
	int length = 0;
	int height = 0;
	// Need more data here to hold resource information

	while (inFile) {

		getline(inFile, lineRead);
		// String tokenizing method: https://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
		std::stringstream strstr(lineRead);
		std::istream_iterator<std::string> it(strstr);
		std::istream_iterator<std::string> end; 
		std::vector<std::string> results(it, end);

		if (results[0].compare("LENGTH") == 0) 
			length = std::stoi(results[1]);
		else if (results[0].compare("HEIGHT") == 0) 
			height = std::stoi(results[1]);		
		else if (results[0].compare("RESOURCE") == 0){
			// TO-DO: Go to gb_map and update the resource nodes
		}
		else if (results[0].compare("DISABLE") == 0) {
			// TO-DO: Go to node in gb_map and disable it. 
		}
	}
	inFile.close();

	std::cout << "Map has been created from " << fileName << "." << std::endl; 

	// Create the graphs using the length and height data from the file
	gb_map.tileGraph->makeGridGraph(length, height, NodeType::TILE);
	gb_map.resourceGraph->makeGridGraph(length * 2, height * 2, NodeType::RESOURCE);
	gb_map.tileGraph->linkResourceNodes(gb_map.resourceGraph); 
	// TO-DO: Use resource data from file to update the above two graphs accordingly. 


}

