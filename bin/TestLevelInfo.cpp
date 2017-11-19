#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Eel.h"
#include "TextureManager.h"
#include <iostream>
#include "util.h"
#include "Minions.h"
#include "XMLParser.h"

int main(int argc, char** argv)
{

  // Resource Managers
  TextureManager textures;
  XMLParser parser;

  parser.loadXML("../data/xml/TestXML.xml");
  parser.loadLevel(1);

  // create main window
  sf::RenderWindow App(sf::VideoMode(1024,768,32), "Level Test",sf::Style::Titlebar|sf::Style::Close);
  Eel fish;
  std::vector<std::shared_ptr<Minions>> minions(5);
  minions[0]=std::make_shared<Minions>(sf::Vector2f(50,50));
  minions[1]=std::make_shared<Minions>(sf::Vector2f(1024,0));
  minions[2]=std::make_shared<Minions>(sf::Vector2f(0,768));
  minions[3]=std::make_shared<Minions>(sf::Vector2f(1024,768));
  minions[4]=std::make_shared<Minions>(sf::Vector2f(0,768/2));

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
  textures.addArea("Minions_normal",sf::IntRect(512,0,256,256));
  textures.addArea("Minions_shocked",sf::IntRect(768,0,256,256));
  textures.addArea("Minions_shot",sf::IntRect(0,256,256,256));
  textures.addArea("Minions_weak",sf::IntRect(256,256,256,256));
  for(int i=0;i<5;i++)
  {
      minions[i]->setTexture(textures.get().texture);
      minions[i]->setTextureAreas(textures.get().areas);
      minions[i]->setHeadDistance(0.01);
      minions[i]->init();
  }
  fish.setTexture(textures.get().texture);
  fish.setTextureAreas(textures.get().areas);

  fish.init();

    // start main loop
  sf::Clock clock;
  /*
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
    float deltaTime=clock.restart().asSeconds(); 
    sf::Vector2i mousePos=sf::Mouse::getPosition(App);
    for(int i=0;i<5;i++)
    {
        sf::Vector2f diff=sf::Vector2f(512,384)-minions[i]->getKnot(0).getPosition();
        if(fish.getState()==Eel::RELEASE&&mag(fish.getCenter()-minions[i]->getKnot(0).getPosition())<fish.getAttackRadius())
        {
                minions[i]->shocked();
        }
        if(fish.getState()==Eel::RELEASED&&minions[i]->getState()==Minions::SHOCKED)
        {
            minions[i]->weaken();
        }
        if(minions[i]->getState()==Minions::NORMAL)
        {
            sf::Vector2f dist=normalize(diff)*50.0f*deltaTime;
            if(mag(dist)>minions[i]->getHeadDistance())
            minions[i]->swimTo(minions[i]->getKnot(0).getPosition()+dist);
            minions[i]->update(0);
        }
        App.draw(*(minions[i]));
    }
    fish.update(deltaTime);
    App.draw(fish);
    App.display();*/
  }

  // Done.
  return 0;
}
