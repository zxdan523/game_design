#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameView.h"
#include "AIView.h"
#include "GameLogic.h"
#include "MusicManager.h"
#include "XMLParser.h"
#include "LevelInfo.h"
#include <iostream>

std::shared_ptr<std::vector<LevelInfo>> loadInLevelInfo()
{
    XMLParser parser;
    parser.loadXML("../data/xml/levels.xml");
    std::shared_ptr<std::vector<LevelInfo>> levels=std::make_shared<std::vector<LevelInfo>>();

    for(int i=1;i<6;i++)
    {
        LevelInfo level;
        parser.loadLevel(level,i);
        levels->push_back(level);
    }
    return levels;
}

int main(int argc, char** argv)
{

  // Resource Managers
  std::shared_ptr<TextureManager> textureManager=std::make_shared<TextureManager>();
  XMLParser parser;
  parser.loadXML("../data/xml/levels.xml");
  parser.loadTexture(*textureManager);
   
  // create main window
  sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32), "FISHNAPPED",sf::Style::Titlebar|sf::Style::Close);

  std::shared_ptr<Larry> larry=std::make_shared<Larry>();
  larry->setTexture(textureManager->get().texture);
  larry->setTextureAreas(textureManager->get().areas);

  std::shared_ptr<Shark> shark1=std::make_shared<Shark>(Shark::SHARK1);
  shark1->setTexture(textureManager->get().texture);
  shark1->setTextureAreas(textureManager->get().areas);
  std::shared_ptr<Shark> shark2=std::make_shared<Shark>(Shark::SHARK2);
  shark2->setTexture(textureManager->get().texture);
  shark2->setTextureAreas(textureManager->get().areas);

  std::shared_ptr<Eel> eel=std::make_shared<Eel>();
  eel->setTexture(textureManager->get().texture);
  eel->setTextureAreas(textureManager->get().areas);


  std::shared_ptr<std::vector<std::shared_ptr<Minions>>> minions=std::make_shared<std::vector<std::shared_ptr<Minions>>>();
  std::shared_ptr<std::vector<std::vector<std::shared_ptr<Swordfish>>>> swordfish=std::make_shared<std::vector<std::vector<std::shared_ptr<Swordfish>>>>();

  std::shared_ptr<PowerUpSystem> powerup=std::make_shared<PowerUpSystem>();
  powerup->setTexture(textureManager->get().texture);
  powerup->setTextureAreas(textureManager->get().areas);

  std::shared_ptr<MusicManager> musicManager=std::make_shared<MusicManager>();
    
  musicManager->addMusic("eel_release.wav");
  musicManager->addMusic("swordfish_shoot.wav");
  musicManager->addMusic("power_up.wav");
  musicManager->addMusic("larry_dead.wav");
  musicManager->addMusic("level_complete.wav");
  musicManager->addMusic("defeat_minion.wav");
  musicManager->addMusic("pass_all.wav");
    
  //musicManager->playBackground("level1_background.wav");
    
  std::shared_ptr<GameView> gameView=std::make_shared<GameView>(larry,minions,shark1,shark2,eel,nullptr,powerup,musicManager,textureManager);
  std::shared_ptr<AIView> aiView=std::make_shared<AIView>(larry,minions,shark1,shark2,eel,nullptr,powerup);
  std::vector<std::shared_ptr<Swordfish>> swd_list;
  for(int i=0;i<5;i++)
  {
      swd_list.push_back(std::make_shared<Swordfish>(sf::Vector2f(i*200,0),sf::Vector2f(1.0f,1.0f)));
      swd_list[swd_list.size()-1]->setTexture(textureManager->get().texture);
      swd_list[swd_list.size()-1]->setTextureAreas(textureManager->get().areas);
  }
  swordfish->push_back(swd_list);
  std::shared_ptr<GameLogic> gameLogic=std::make_shared<GameLogic>(larry,minions,swordfish,shark1,shark2,eel,powerup,gameView,aiView,textureManager,loadInLevelInfo());
  gameLogic->levelStart();
  // start main loop
  sf::Clock clock;
  while(App.isOpen())
  {
    sf::Vector2i mousePos=sf::Mouse::getPosition(App);
    // process events
    sf::Event event;
     while (App.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                App.close();
                break;
            case sf::Event::KeyPressed:
                gameLogic->keyPressed(event.key.code,mousePos.x,mousePos.y);
            default:
                break;
        }
       
    }
     gameLogic->mouseMoved(mousePos.x,mousePos.y);
    // clear screen and fill with blue
    App.clear(sf::Color::Blue);
    gameLogic->run(clock.restart().asSeconds());
    App.draw(*gameView);
    App.display();
  }

  // Done.
  return 0;
}
