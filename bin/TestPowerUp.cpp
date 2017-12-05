#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PowerUpSystem.h"
#include "TextureManager.h"
#include <iostream>

int main(int argc, char** argv)
{

  // Resource Managers
  TextureManager textures;

  // create main window
  sf::RenderWindow App(sf::VideoMode(1024,768,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);
  PowerUpSystem ps;;

    /*Note: to save the memory fot passing texture and texture location, I used shared pointer. However, shared pointer can only be created dynamically, so you need to use make_shared<T>, or you will have segementation fault*/
  textures.addTexture("../data/fish.png"); 
  textures.addArea("TimeMachine",sf::IntRect(896,768,128,128));
  textures.addArea("TimeMachineBubble",sf::IntRect(512,896,128,128));
  textures.addArea("TimeMachineLogo",sf::IntRect(640,896,128,128));
  textures.addArea("Octopus",sf::IntRect(256,768,256,256));
  textures.addArea("OctopusBubble",sf::IntRect(512,768,128,128));
  textures.addArea("OctopusLogo",sf::IntRect(768,768,128,128));
  textures.addArea("Decoy",sf::IntRect(896,896,128,128));
  textures.addArea("DecoyBubble",sf::IntRect(640,768,128,128));
  textures.addArea("DecoyLogo",sf::IntRect(768,896,128,128));

  ps.setTexture(textures.get().texture);
  ps.setTextureAreas(textures.get().areas);

  ps.init();
    // start main loop
  
  sf::Clock clock;
  sf::Vector2i mousePos;
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
                mousePos=sf::Mouse::getPosition(App);
                if(event.key.code==sf::Keyboard::A)
                {
                    ps.useTool(PowerUp::TIME_MACHINE,sf::Vector2f(mousePos.x,mousePos.y));
                }
                if(event.key.code==sf::Keyboard::S)
                {
                    ps.useTool(PowerUp::OCTOPUS,sf::Vector2f(mousePos.x,mousePos.y));
                }
                if(event.key.code==sf::Keyboard::D)
                {
                    ps.useTool(PowerUp::DECOY,sf::Vector2f(mousePos.x,mousePos.y));
                }
            default:
                break;
        }
       
    }

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);
    mousePos=sf::Mouse::getPosition(App);
    ps.grabToolBubble(sf::Vector2f(mousePos.x,mousePos.y),10.0f);
    ps.update(clock.restart().asSeconds());
    App.draw(ps);
    App.display();
  }

  // Done.
  return 0;
}
