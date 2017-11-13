#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

// modified version of SFML example. Tiles in the game are made up of triangles and squares.
class TileMap : public sf::Drawable, public sf::Transformable
{

public:

	bool load(TextureManager &textureManager, std::string terrain, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height)
	{
		// texture coordinates
		textureAreas = textureManager.get("terrain").areas;
		texture = textureManager.get("terrain").texture;

        // resize the vertex array to fit the level size
		quads.setPrimitiveType(sf::Quads);
		triangles.setPrimitiveType(sf::Triangles);
		quads.resize(width * height * 4);
		triangles.resize(width * height * 3);

        // populate the vertex array, with one quad per tile
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
                // current tile
				int tileNumber = tiles[i + j * width];

				if(tileNumber == 1) {
					sf::Vertex* quad = &quads[(i + j * width) * 4];

                // square
					quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
					quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

					quad[0].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top);
					quad[1].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top);
					quad[2].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top + tileSize.y);
					quad[3].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top + tileSize.y);					
				}
				// triangle top right
				else if(tileNumber == 2) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					triangle[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

					triangle[0].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top);
					triangle[1].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top);
					triangle[2].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top + tileSize.y);
				}
				// triangle top left
				else if(tileNumber == 3) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

					triangle[0].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top);
					triangle[1].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top);
					triangle[2].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top + tileSize.y);
				}
				// triangle bottom right
				else if(tileNumber == 4) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

					triangle[0].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top + tileSize.y);
					triangle[1].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top);
					triangle[2].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top + tileSize.y);
				}
				// triangle bottom left
				else if(tileNumber == 5) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
					triangle[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

					triangle[0].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top);
					triangle[1].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top + tileSize.y);
					triangle[2].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top + tileSize.y);
				}
				// triangle small top
				else if(tileNumber == 6) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x + tileSize.x/2, j * tileSize.y + tileSize.y/2);

					triangle[0].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top);
					triangle[1].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top);
					triangle[2].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x/2, (*textureAreas)[terrain].top + tileSize.y/2);
				}
				// triangle small left
				else if(tileNumber == 7) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x + tileSize.x/2, j * tileSize.y + tileSize.y/2);

					triangle[0].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top);
					triangle[1].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top + tileSize.y);
					triangle[2].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x/2, (*textureAreas)[terrain].top + tileSize.y/2);
				}
				// triangle small bottom
				else if(tileNumber == 8) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x + tileSize.x/2, j * tileSize.y + tileSize.y/2);

					triangle[0].texCoords = sf::Vector2f((*textureAreas)[terrain].left, (*textureAreas)[terrain].top + tileSize.y);
					triangle[1].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top + tileSize.y);
					triangle[2].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x/2, (*textureAreas)[terrain].top + tileSize.y/2);
				}
				// triangle small right
				else if(tileNumber == 9) {
					sf::Vertex* triangle = &triangles[(i + j * width) * 3];
					triangle[0].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
					triangle[2].position = sf::Vector2f(i * tileSize.x + tileSize.x/2, j * tileSize.y + tileSize.y/2);

					triangle[0].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top);
					triangle[1].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x, (*textureAreas)[terrain].top + tileSize.y);
					triangle[2].texCoords = sf::Vector2f((*textureAreas)[terrain].left + tileSize.x/2, (*textureAreas)[terrain].top + tileSize.y/2);
				}
			}
			return true;
		}

	private:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
        // apply the transform
			states.transform *= getTransform();

			states.texture = texture.get();

        // draw the vertex array
			target.draw(quads, states);
			target.draw(triangles, states);
		}

		sf::VertexArray quads;
		sf::VertexArray triangles;
		std::shared_ptr<sf::Texture> texture;
		std::shared_ptr<std::map<std::string,sf::IntRect>> textureAreas;
	};


#endif