#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

//#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>
#include <utility>
#include <stdexcept>
#include <cassert>

struct Atlas {
    std::shared_ptr<std::map<std::string,sf::IntRect>> areas;
    std::shared_ptr<sf::Texture> texture;
};

class TextureManager
{
    public:
    	//TextureManager();
    	Atlas get(std::string);
 		void add(std::string, std::string, std::shared_ptr<std::map<std::string,sf::IntRect>>);

    private:
		std::map<std::string, Atlas> atlasMap;
};

#endif