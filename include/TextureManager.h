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

/****************************************************************
 * we try to maintain little number of textures. Ideally, we may
 * just have only one texture which includes the texture of Larry,
 * Shark, Minors, Eel .ect as well as the background.
 *
 * We may also have more textures than we though which could make it
 * exceeds the texture buffer limit. So we prepare more Atlas
 * **************************************************************/

struct Atlas {
    std::shared_ptr<std::map<std::string,sf::IntRect>> areas;
    std::shared_ptr<sf::Texture> texture;
};

class TextureManager
{
    public:
    	//TextureManager();
    	Atlas get(std::string type="default") const;
 		void addArea(std::string id, sf::IntRect area,std::string type="default");
        void addTexture(std::string path,std::string type="default");

    private:
		std::map<std::string, Atlas> atlasMap;
};

#endif
