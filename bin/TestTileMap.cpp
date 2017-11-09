#include <SFML/Graphics.hpp> 
#include "TextureManager.h"
#include "TileMap.h"
#include "XMLParser.h"
#include <iostream>

int main(int argc, char** argv)
{

    // create main window
  sf::RenderWindow App(sf::VideoMode(640,640,32), "Tile Map Test",sf::Style::Titlebar|sf::Style::Close);

   // define the level with an array of tile indices
    /*const int level[] =
    {
      0,1,0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,1,0,0,0,
      0,1,0,0,1,1,1,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,9,1,1,1,
      0,0,0,0,0,0,0,2,3,0,
      0,0,0,0,0,0,0,0,0,0,
      0,9,5,0,0,0,0,0,0,0,
      0,4,3,0,0,0,0,0,0,0,
      4,1,5,0,4,5,0,0,0,0,
    };*/

  XMLParser parser;
  parser.loadXML("../data/xml/TestXML.xml");
  std::vector<int> tiles = parser.getTileMap();

    // create the tilemap from the level definition
  TileMap map;
  TextureManager textures;
  parser.loadTexture(textures,"terrain");
  if (!map.load(textures,"grass", sf::Vector2u(64, 64), tiles, 10, 10))
    return -1;

    // start main loop
  while(App.isOpen())
  {

    sf::Event event;
    while (App.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
        App.close();
        default:
        break;
      }

    }

      // clear screen and fill with blue
    App.clear(sf::Color::Black);
    App.draw(map);
    // display
    App.display();
  }

    // Done.
  return 0;
}
