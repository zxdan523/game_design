#include "TextureManager.h"


void TextureManager::addTexture(std::string path,std::string type)
{
    if(atlasMap.find(type)!=atlasMap.end())
    {
        throw std::runtime_error("inserting existing texture");
    }
    
    std::shared_ptr<sf::Texture> texture=std::make_shared<sf::Texture>();
	if (!texture->loadFromFile(path))
		throw std::runtime_error("error");
    
    atlasMap[type].texture=texture;
    atlasMap[type].areas=std::make_shared<std::map<std::string,sf::IntRect>>();
}
void TextureManager::addArea(std::string id, sf::IntRect area, std::string type)
{
      //textureMap.loadResource(id, path);
      if(atlasMap.find(type)==atlasMap.end())
      {
          throw std::runtime_error("add texture coordinates into a empty texture");
      }
      atlasMap[type].areas->insert(std::make_pair(id,area));
}

Atlas TextureManager::get(std::string type) const
{
	auto found = atlasMap.find(type);
	assert(found != atlasMap.end());
	return (found->second);
}
