#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "TileMap.h"
#include <iostream>

int main(int argc, char** argv)
{

    // create main window
  sf::RenderWindow App(sf::VideoMode(1000,800,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);

   // define the level with an array of tile indices
    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 8))
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
    // display
    App.display();
  }

    // Done.
  return 0;
}
