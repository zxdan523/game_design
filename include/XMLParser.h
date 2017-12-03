#ifndef XMLPARSER_H
#define XMLPARSER_H

//#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "TextureManager.h"
#include <string>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

class XMLParser
{
    public:
    	//XMLParser();
    	void loadXML(const char*);
		std::map<std::string,int> loadLevel(int levelName);
    	void loadTexture(TextureManager&,std::string type="default");
    	void loadFont();
    	std::vector<int> getTileMap();
        std::vector<int> getSwordfishPositions();

    private:
    	tinyxml2::XMLDocument doc;
    	
};

#endif