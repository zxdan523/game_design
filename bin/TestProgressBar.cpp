#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ProgressBar.h"
#include "TextureManager.h"
#include <iostream>

int main(int argc, char** argv)
{

  // create main window
  sf::RenderWindow App(sf::VideoMode(1000,800,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);

  ProgressBar bar(100,10,100,75,sf::Color(0,255,0));
    // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event event;
     while (App.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                App.close();
                break;
            default:
                break;
        }
       
    }

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

    sf::Vector2i mousePos=sf::Mouse::getPosition(App);
    bar.setPosition(sf::Vector2f(mousePos.x,mousePos.y));
    App.draw(bar);
    App.display();
  }

  // Done.
  return 0;
}
