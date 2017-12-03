#include "XMLParser.h"
#include <iostream>

void XMLParser::loadXML(const char* path) {
	doc.LoadFile(path);
}

void XMLParser::loadFont() {

}

std::map<std::string,int> XMLParser::loadLevel(int levelName)
{
	std::map<std::string,int> map;

	// go to level list
	tinyxml2::XMLNode * root = doc.FirstChild();
	tinyxml2::XMLElement * levelList = root->FirstChildElement("LevelList");

	// find specified level
	tinyxml2::XMLElement * level = levelList->FirstChildElement();
	while(level!=NULL && (std::stoi(level->FirstChildElement("name")->GetText()))!=(levelName)) {
		level=level->NextSiblingElement();
	}

	tinyxml2::XMLElement * element = level->FirstChildElement("TileMap");


}

std::vector<int> XMLParser::getTileMap() {
	tinyxml2::XMLNode * root = doc.FirstChild();
	tinyxml2::XMLElement * tileMap = root->FirstChildElement("TileMap");
	std::string tileMapText = tileMap->GetText();

	std::stringstream ss(tileMapText);

	int i;
	std::vector<int> v;
	while(ss>> i) {
		v.push_back(i);
		if(ss.peek()==',')
			ss.ignore();
	}

	return v;
}

std::vector<int> XMLParser::getSwordfishPositions() {
    tinyxml2::XMLNode * root = doc.FirstChild();
    tinyxml2::XMLElement * swordfishAlgorithmList = root->FirstChildElement("SwordFishAlgorithmList");
    tinyxml2::XMLElement * swordfishAlgorithm = swordfishAlgorithmList->FirstChildElement("Algorithm");
    tinyxml2::XMLElement * swordfishPositions = swordfishAlgorithm->FirstChildElement("position");
    std::string positions = swordfishPositions->GetText();
    
    std::stringstream ss(positions);
    
    int i;
    std::vector<int> v;
    while(ss>> i) {
        v.push_back(i);
        if(ss.peek()==',')
            ss.ignore();
    }
    
    return v;
}

// adds texture info from the XML file to the texture manager 
void XMLParser::loadTexture(TextureManager &textures, std::string name) {
	// Find specific texture needed
	tinyxml2::XMLNode * root = doc.FirstChild();
	tinyxml2::XMLElement * textureList = root->FirstChildElement("TextureList");
	tinyxml2::XMLElement * texture = textureList->FirstChildElement();
	while(texture!=NULL && (texture->FirstChildElement("name")->GetText())!=(name)) {
		texture=texture->NextSiblingElement();
	}
//		std::cout<<texture->FirstChildElement("name")->GetText()<<std::endl;

	// sets location of texture
	tinyxml2::XMLElement * location = texture->FirstChildElement("location");
	textures.addTexture(location->GetText(),name);

	// iterate through areas listed and add to texture manager
	for(tinyxml2::XMLElement * item = texture->FirstChildElement("Positions")->FirstChildElement();
		item!= NULL;item=item->NextSiblingElement()) {
		std::string itemText = item->GetText();
	std::string areaName = (itemText).substr(0, (itemText).find("|"));
	std::string value = (itemText).substr((itemText).find("|")+1);
	std::stringstream ss(value);

	int i;
	std::vector<int> v;
	while(ss>> i) {
		v.push_back(i);
		if(ss.peek()==',')
			ss.ignore();
	}
	textures.addArea(areaName,sf::IntRect(v.at(0),v.at(1),v.at(2),v.at(3)),name);
}
}