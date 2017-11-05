#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "TileMap.h"
#include <iostream>

int main(int argc, char** argv)
{

    // create main window
  sf::RenderWindow App(sf::VideoMode(640,640,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);

   // define the level with an array of tile indices
    const int level[] =
    {
      9,9,9,9,9,9,9,9,3,2,
      9,9,9,9,9,9,9,3,2,9,
      9,9,9,7,9,9,9,0,9,9,
      9,9,9,1,4,9,9,0,9,9,
      9,9,9,9,1,4,9,9,9,9,
      9,0,9,9,9,1,4,9,9,9,
      9,0,9,9,9,8,0,0,0,0,
      9,0,9,9,9,9,9,9,9,9,
      3,0,4,9,9,9,9,9,9,9,
      0,0,2,9,9,9,9,9,9,9,
    };

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("tileset.png", sf::Vector2u(64, 64), level, 10, 10))
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
    App.clear(sf::Color::Blue);
    App.draw(map);
    //App.draw(map.m_vertices);
    //App.draw(map.triangles);
    // display
    App.display();
  }

    // Done.
  return 0;
}
