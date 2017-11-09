#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Eel.h"
#include "TextureManager.h"
#include <iostream>

int main(int argc, char** argv)
{

  // Resource Managers
  TextureManager textures;

  // create main window
  sf::RenderWindow App(sf::VideoMode(1024,768,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);
  Eel fish;

    /*Note: to save the memory fot passing texture and texture location, I used shared pointer. However, shared pointer can only be created dynamically, so you need to use make_shared<T>, or you will have segementation fault*/
  textures.addTexture("../data/fish.png"); 
  textures.addArea("Eel_left_eye",sf::IntRect(512,256,64,64));
  textures.addArea("Eel_right_eye",sf::IntRect(512,320,64,64));
  textures.addArea("Eel_attack_left_eye",sf::IntRect(512,384,64,64));
  textures.addArea("Eel_attack_right_eye",sf::IntRect(512,448,64,64));
  textures.addArea("Eel_left_fin",sf::IntRect(576,256,64,64));
  textures.addArea("Eel_right_fin",sf::IntRect(576,320,64,64));
  textures.addArea("Eel_mouth",sf::IntRect(576,384,64,64));
  textures.addArea("Eel_tail",sf::IntRect(576,448,64,64));


  fish.setTexture(textures.get().texture);
  fish.setTextureAreas(textures.get().areas);

  fish.init();
    // start main loop
  sf::Clock clock;
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
                        fish.triggered();
                break;
            default:
                break;
        }
       
    }

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

    sf::Vector2i mousePos=sf::Mouse::getPosition(App);
    fish.update(clock.restart().asSeconds());
    App.draw(fish);
    App.display();
  }

  // Done.
  return 0;
}
