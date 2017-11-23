#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Swordfish.h"
#include "TextureManager.h"
#include <iostream>
#include <vector>
#include "Constants.h"
int main(int argc, char** argv)
{

  // Resource Managers
  TextureManager textures;

  // create main window
  sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);
  std::vector<std::shared_ptr<Swordfish>> fish(5);
  

  /*Note: to save the memory fot passing texture and texture location, I used shared pointer. However, shared pointer can only be created dynamically, so you need to use make_shared<T>, or you will have segementation fault*/
  textures.addTexture("../data/fish.png"); 
  textures.addArea("Swordfish",sf::IntRect(512,512,512,256));
  textures.addArea("bubble",sf::IntRect(960,256,64,64));
  for(int i=0;i<5;i++)
  {
      fish[i]=std::make_shared<Swordfish>(sf::Vector2f(i*200+1,1),sf::Vector2f(1.0f,1.0f));
      fish[i]->setTexture(textures.get().texture);
      fish[i]->setTextureAreas(textures.get().areas);
      fish[i]->init();
  }
 
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
                    break;
                default:
                    break;
            }
        }
      // clear screen and fill with blue
      App.clear(sf::Color::Blue);

      sf::Vector2i mousePos=sf::Mouse::getPosition(App);
      float deltaTime=clock.restart().asSeconds();
      for(int i=0;i<5;i++)
      {
        fish[i]->update(deltaTime);
        App.draw(*fish[i]);
      }
      App.display();
    }

  // Done.
  return 0;
}
