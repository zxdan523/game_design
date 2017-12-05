#include "TerrainManager.h"
#include <iostream>

void TerrainManager::load(std::vector<std::vector<sf::Vector2f>> polygon_list, sf::Color color)
{
	sf::ConvexShape shape;
	sf::ConvexShape shape_hitbox;
	std::vector<std::vector<sf::Vector2f>>::iterator shapeIterator;
	std::vector<sf::Vector2f>::iterator pointIterator;
	int pointCount;

	for(shapeIterator = polygon_list.begin(); shapeIterator != polygon_list.end(); shapeIterator++ )    {
		shape.setPointCount((*shapeIterator).size());
		std::vector<sf::Vector2f> shape_hitbox_points;
		for(pointCount = 0,pointIterator = (*shapeIterator).begin(); pointIterator != (*shapeIterator).end(); pointIterator++,pointCount++ )    {
			shape.setPoint(pointCount,*pointIterator);
		}
		shape.setFillColor(color);
		shape_list.push_back(shape);
	}

}

void TerrainManager::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
        // apply the transform
	states.transform *= getTransform();

		//states.texture = texture.get();
	for (auto const& i : shape_list) {
		target.draw(i,states);
	}
	}