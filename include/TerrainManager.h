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
	void load(std::vector<std::vector<sf::Vector2f>>, sf::Color color = sf::Color::White);
	std::vector<std::vector<sf::Vector2f>> getTerrainHitbox();

protected:
	virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
	std::vector<sf::ConvexShape> shape_list;
};


#endif