#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Larry.h"
#include "MusicManager.h"
#include <iostream>

using namespace sf;
using namespace std;

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);
    Larry fish;
    /*Note: to save the memory fot passing texture and texture location, I used shared pointer. However, shared pointer can only be created dynamically, so you need to use make_shared<T>, or you will have segementation fault*/
    std::shared_ptr<sf::Texture> texture=std::make_shared<sf::Texture>();
    texture->loadFromFile("../data/Larry.png");
    fish.setTexture(texture);
    std::shared_ptr<std::map<std::string,sf::IntRect>> areas=std::make_shared<std::map<std::string,sf::IntRect>>();
    (*areas)["Larry_eye"]=sf::IntRect(256,192,64,64);
    (*areas)["Larry_mouth"]=sf::IntRect(320,0,128,128);
    (*areas)["Larry_fin_big_left"]=sf::IntRect(0,128,128,128);
    (*areas)["Larry_fin_big_right"]=sf::IntRect(0,0,128,128);
    (*areas)["Larry_fin_tiny_left"]=sf::IntRect(256,64,64,64);
    (*areas)["Larry_fin_tiny_right"]=sf::IntRect(256,0,64,64);
    (*areas)["Larry_tail"]=sf::IntRect(128,0,128,256);
    fish.setTextureAreas(areas);
    fish.init();
    
    MusicManager music;
    music.add();
        // start main loop
  while(App.isOpen())
  {
      
    
    // process events
    Event event;
    while (App.pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                App.close();
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape)
                    App.close();
                else if (event.key.code == Keyboard::Num1)
                    music.play("canary");
                else if (event.key.code == Keyboard::Num2)
                    music.play("orchestral");
                else if (event.key.code == Keyboard::Num3)
                    music.play("ding");
                else if (event.key.code == Keyboard::P)
                    music.stop();
            default:
                break;
        }
    }
      
    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

    sf::Vector2i mousePos=sf::Mouse::getPosition(App);
    fish.swimTo(sf::Vector2f(mousePos.x,mousePos.y));
    App.draw(fish);
      
    // display
    App.display();
  }

  // Done.
  return 0;
}
