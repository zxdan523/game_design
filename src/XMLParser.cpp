#include "XMLParser.h"

void XMLParser::loadXML(const char* path) {
	doc.LoadFile(path);
}

void XMLParser::loadFont() {

}

// adds texture info from the XML file to the texture manager 
void XMLParser::loadTexture(TextureManager &textures) {
	// Find elements in XML
	tinyxml2::XMLNode * root = doc.FirstChild();
	tinyxml2::XMLElement * main = root->FirstChildElement("TextureInfo");
	tinyxml2::XMLElement * location = main->FirstChildElement("location");

	textures.addTexture(location->GetText());

	// iterate through areas listed and add to texture manager
	for(tinyxml2::XMLElement * item = main->FirstChildElement("Positions")->FirstChildElement();
		item!= NULL;item=item->NextSiblingElement()) {
		std::string itemText = item->GetText();
	std::string name = (itemText).substr(0, (itemText).find("|"));
	std::string value = (itemText).substr((itemText).find("|")+1);
	std::stringstream ss(value);

	int i;
	std::vector<int> v;
	while(ss>> i) {
		v.push_back(i);
		if(ss.peek()==',')
			ss.ignore();
	}
	textures.addArea(name,sf::IntRect(v.at(0),v.at(1),v.at(2),v.at(3)));
}
}