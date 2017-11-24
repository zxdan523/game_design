#include "TerrainManager.h"

void TerrainManager::load(std::vector<std::vector<sf::Vector2f>> polygons)
{
		//polygons = std::make_shared<std::list<sf::ConvexShape>>();
	sf::ConvexShape shape;
	std::vector<std::vector<sf::Vector2f>>::iterator shapeIterator;
	std::vector<sf::Vector2f>::iterator pointIterator;
	int pointCount;
	for(shapeIterator = polygons.begin(); shapeIterator != polygons.end(); shapeIterator++ )    {
		shape.setPointCount((*shapeIterator).size());
		for(pointCount = 0,pointIterator = (*shapeIterator).begin(); pointIterator != (*shapeIterator).end(); pointIterator++,pointCount++ )    {
			shape.setPoint(pointCount,*pointIterator);
		}
		v.push_back(shape);
	}

		//(*polygons).push_front(shape);
}

void TerrainManager::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
        // apply the transform
	states.transform *= getTransform();

		//states.texture = texture.get();
	for (auto const& i : v) {
		target.draw(i,states);
	}
	
		//target.draw((*polygons).front(),states);
}