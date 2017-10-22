#include "TextureManager.h"

/*TextureManager::TextureManager()
{
	
}*/

void TextureManager::add(std::string id, std::string path, std::shared_ptr<std::map<std::string,sf::IntRect>> areas)
{
      //textureMap.loadResource(id, path);
	std::shared_ptr<sf::Texture> texture=std::make_shared<sf::Texture>();
	if (!texture->loadFromFile(path))
		throw std::runtime_error("error");

	Atlas input;
	input.areas = areas;
	input.texture = texture;
	atlasMap.insert(std::make_pair(id, input));
}

Atlas TextureManager::get(std::string id)
{
	auto found = atlasMap.find(id);
	assert(found != atlasMap.end());
	return (found->second);
}