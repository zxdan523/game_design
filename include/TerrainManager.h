#ifndef TERRAINMANAGER_H
#define TERRAINMANAGER_H
#include <SFML/Graphics.hpp>
#include <TextureManager.h>
#include <vector>
#include <list>
#include <memory>
#include <string>

// modified version of SFML example. Tiles in the game are made up of triangles and squares.
class TerrainManager : public sf::Drawable, public sf::Transformable
{

public:
	void load(std::vector<std::vector<sf::Vector2f>>);


protected:
	virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
	std::vector<sf::ConvexShape> v;
	sf::ConvexShape a;
	//std::shared_ptr<std::list<sf::ConvexShape>> polygons;
	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<std::map<std::string,sf::IntRect>> textureAreas;
};


#endif