#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameView.h"
#include "AIView.h"
#include "GameLogic.h"
#include "MusicManager.h"
#include <iostream>

int main(int argc, char** argv)
{

  // Resource Managers
  std::shared_ptr<TextureManager> textureManager=std::make_shared<TextureManager>();
  textureManager->addTexture("../data/fish.png");
  textureManager->addArea("Larry_eye",sf::IntRect(256,192,64,64));
  textureManager->addArea("Larry_mouth",sf::IntRect(320,0,128,128));
  textureManager->addArea("Larry_fin_big_left",sf::IntRect(0,128,128,128));
  textureManager->addArea("Larry_fin_big_right",sf::IntRect(0,0,128,128));
  textureManager->addArea("Larry_fin_tiny_left",sf::IntRect(256,64,64,64));
  textureManager->addArea("Larry_fin_tiny_right",sf::IntRect(256,0,64,64));
  textureManager->addArea("Larry_tail",sf::IntRect(128,0,128,256));
   textureManager->addArea("bubble",sf::IntRect(960,256,64,64));
   textureManager->addArea("Minions_normal",sf::IntRect(512,0,256,256));
   textureManager->addArea("Minions_shocked",sf::IntRect(768,0,256,256));
   textureManager->addArea("Minions_shot",sf::IntRect(0,256,256,256));
   textureManager->addArea("Minions_weak",sf::IntRect(256,256,256,256));
   textureManager->addArea("Eel_left_eye",sf::IntRect(512,256,64,64));
   textureManager->addArea("Eel_right_eye",sf::IntRect(512,320,64,64));
   textureManager->addArea("Eel_attack_left_eye",sf::IntRect(512,384,64,64));
   textureManager->addArea("Eel_attack_right_eye",sf::IntRect(512,448,64,64));
   textureManager->addArea("Eel_left_fin",sf::IntRect(576,256,64,64));
   textureManager->addArea("Eel_right_fin",sf::IntRect(576,320,64,64));
   textureManager->addArea("Eel_mouth",sf::IntRect(580,384,60,64));
   textureManager->addArea("Eel_tail",sf::IntRect(576,448,64,64));
   textureManager->addArea("Swordfish",sf::IntRect(512,512,512,256));
   textureManager->addArea("Shark_normal_head",sf::IntRect(0,512,256,256));
   textureManager->addArea("Shark_weak_head",sf::IntRect(256,512,256,256));
   textureManager->addArea("Shark_crazy_head",sf::IntRect(633,256,256,256));
   textureManager->addArea("Shark_fins",sf::IntRect(886,256,64,128));
   textureManager->addArea("Shark_tail",sf::IntRect(886,384,64,128));
   textureManager->addArea("Shark_normal_head2",sf::IntRect(0,1024,256,256));
   textureManager->addArea("Shark_weak_head2",sf::IntRect(512,1024,256,256));
   textureManager->addArea("Shark_crazy_head2",sf::IntRect(256,1024,256,256));
   	textureManager->addArea("Shark_fins2",sf::IntRect(768,1024,64,128));
   	textureManager->addArea("Shark_tail2",sf::IntRect(769,1152,63,128));
   	textureManager->addArea("TimeMachine",sf::IntRect(896,768,128,128));
   	textureManager->addArea("TimeMachineBubble",sf::IntRect(512,896,128,128));
   	textureManager->addArea("TimeMachineLogo",sf::IntRect(640,896,128,128));
   	textureManager->addArea("Octopus",sf::IntRect(256,768,256,256));
   	textureManager->addArea("OctopusBubble",sf::IntRect(512,768,128,128));
   textureManager->addArea("OctopusLogo",sf::IntRect(768,768,128,128));
   textureManager->addArea("Decoy",sf::IntRect(896,896,128,128));
   textureManager->addArea("DecoyBubble",sf::IntRect(640,768,128,128));
   textureManager->addArea("DecoyLogo",sf::IntRect(768,896,128,128));
   textureManager->addArea("Eel",sf::IntRect(1024,256,256,256));
   textureManager->addArea("Shark1",sf::IntRect(0,768,256,256));
   textureManager->addArea("Shark2",sf::IntRect(1024,0,256,256));
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
    
  musicManager->addMusic("orchestral.ogg");
  musicManager->addMusic("canary.wav");
  musicManager->addMusic("ding.flac");

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
  std::shared_ptr<GameLogic> gameLogic=std::make_shared<GameLogic>(larry,minions,swordfish,shark1,shark2,eel,powerup,gameView,aiView,textureManager);
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
