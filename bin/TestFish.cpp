#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Larry.h"
#include "TextureManager.h"
#include <iostream>

int main(int argc, char** argv)
{

  // Resource Managers
  TextureManager textures;

  // create main window
  sf::RenderWindow App(sf::VideoMode(1000,800,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);
  Larry fish;

    /*Note: to save the memory fot passing texture and texture location, I used shared pointer. However, shared pointer can only be created dynamically, so you need to use make_shared<T>, or you will have segementation fault*/
  textures.addTexture("../data/fish.png"); 
  textures.addArea("Larry_eye",sf::IntRect(256,192,64,64));
  textures.addArea("Larry_mouth",sf::IntRect(320,0,128,128));
  textures.addArea("Larry_fin_big_left",sf::IntRect(0,128,128,128));
  textures.addArea("Larry_fin_big_right",sf::IntRect(0,0,128,128));
  textures.addArea("Larry_fin_tiny_left",sf::IntRect(256,64,64,64));
  textures.addArea("Larry_fin_tiny_right",sf::IntRect(256,0,64,64));
  textures.addArea("Larry_tail",sf::IntRect(128,0,128,256));


  fish.setTexture(textures.get().texture);
  fish.setTextureAreas(textures.get().areas);

  fish.init();
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
    fish.swimTo(sf::Vector2f(mousePos.x,mousePos.y));
    fish.update(0);
    App.draw(fish);
    App.display();
  }

  // Done.
  return 0;
}
