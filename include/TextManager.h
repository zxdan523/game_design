#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

//#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>
#include <utility>
#include <stdexcept>
#include <cassert>

class TextManager
{
    public:
    	TextManager();
    	std::shared_ptr<sf::Text> getText(std::string);
    	std::shared_ptr<sf::Font> getFont(std::string);
 		void addFont(std::string, std::string);
 		void addText(std::string, sf::Text);

    private:
    	std::map<std::string, std::shared_ptr<sf::Text>> textMap;
    	std::map<std::string, std::shared_ptr<sf::Font>> fontMap;
};

#endif