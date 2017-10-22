#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>
#include <utility>
#include <stdexcept>
#include <cassert>

using namespace std;

template <typename Key, typename Resource>
class ResourceManager
{

public:
	void loadResource(Key id, const std::string& filename);
	std::shared_ptr<Resource> getResource(Key id);
	//const sf::Texture& get(string s) const;
	
private:
	std::map<Key,std::shared_ptr<Resource>> mResourceMap;
	//void insertResource(Key id, std::shared_ptr<Resource> resource);

};

// loads the SFML resource into memory
template <typename Key, typename Resource>
void ResourceManager<Key, Resource>::loadResource(Key id, const std::string& filename)
{
	// Create and load resource
	//std::shared_ptr<Resource> resource(new Resource());
	std::shared_ptr<Resource> resource=std::make_shared<Resource>();
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);


	mResourceMap.insert(std::make_pair(id, std::move(resource)));
}


template <typename Key, typename Resource>
std::shared_ptr<Resource> ResourceManager<Key, Resource>::getResource(Key id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return found->second;
}


#endif