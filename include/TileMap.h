#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <memory>
#include <string>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:



	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
	{

        // resize the vertex array to fit the level size
		quads.setPrimitiveType(sf::Quads);
		triangles.setPrimitiveType(sf::Triangles);
		quads.resize(width * height * 4);
		triangles.resize(width * height * 3);

        // populate the vertex array, with one quad per tile
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
                // get the current tile number
				int tileNumber = tiles[i + j * width];

				if(tileNumber == 0) {
					sf::Vertex* quad = &quads[(i + j * width) * 4];

                // define its 4 corners
					quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
					quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
					/*quad[0].color = sf::Color::Green;
					quad[1].color = sf::Color::Green;
					quad[2].color = sf::Color::Green;
					quad[3].color = sf::Color::Green;*/
				}

				if(tileNumber == 1) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					triangle[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				}

				if(tileNumber == 2) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
				}

				if(tileNumber == 3) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
				}

				if(tileNumber == 4) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
					triangle[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				}

				if(tileNumber == 5) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x + tileSize.x/2, j * tileSize.y + tileSize.y/2);
				}

				if(tileNumber == 6) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x + tileSize.x/2, j * tileSize.y + tileSize.y/2);
				}

				if(tileNumber == 7) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x + tileSize.x/2, j * tileSize.y + tileSize.y/2);
				}

				if(tileNumber == 8) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x + tileSize.x/2, j * tileSize.y + tileSize.y/2);
				}

                
			}

			return true;
		}

//private:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        //states.texture = &m_tileset;

        // draw the vertex array
			target.draw(quads, states);
			target.draw(triangles, states);
		}

		sf::VertexArray quads;
		sf::VertexArray triangles;
		sf::Texture m_tileset;

	};


#endif