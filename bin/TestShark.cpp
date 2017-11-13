#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Shark.h"
#include "TextureManager.h"
#include <iostream>

int main(int argc, char** argv)
{

  // Resource Managers
  TextureManager textures;

  // create main window
  sf::RenderWindow App(sf::VideoMode(1000,800,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);
  Shark fish;

    /*Note: to save the memory fot passing texture and texture location, I used shared pointer. However, shared pointer can only be created dynamically, so you need to use make_shared<T>, or you will have segementation fault*/
  textures.addTexture("../data/fish.png"); 
  textures.addArea("Shark_normal_head",sf::IntRect(0,512,256,256));
  textures.addArea("Shark_weak_head",sf::IntRect(256,512,256,256));
  textures.addArea("Shark_crazy_head",sf::IntRect(633,256,256,256));
  textures.addArea("Shark_fins",sf::IntRect(886,256,64,128));
  textures.addArea("Shark_tail",sf::IntRect(886,384,64,128));


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
            case sf::Event::KeyPressed:
                if(event.key.code==sf::Keyboard::A)
                {
                    fish.shocked();
                }
                if(event.key.code==sf::Keyboard::S)
                {
                    fish.shot();
                }
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
