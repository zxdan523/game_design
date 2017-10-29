  #include <SFML/Graphics.hpp>
  #include <SFML/Audio.hpp>
  #include "Larry.h"
  #include "TextureManager.h"
  #include "TextManager.h"
  #include "MusicManager.h"
  #include <iostream>

  int main(int argc, char** argv)
  {

    // Resource Managers
    TextureManager textures;
    TextureManager testTextures;
    MusicManager music;
    music.add();
    TextManager texts;
    bool isTest = false;

    // create main window
    sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);
    Larry fish;
    Larry testFish;

      /*Note: to save the memory fot passing texture and texture location, I used shared pointer. However, shared pointer can only be created dynamically, so you need to use make_shared<T>, or you will have segementation fault*/
    textures.addTexture("../data/Default.png"); 
    textures.addArea("Larry_eye",sf::IntRect(256,192,64,64));
    textures.addArea("Larry_mouth",sf::IntRect(320,0,128,128));
    textures.addArea("Larry_fin_big_left",sf::IntRect(0,128,128,128));
    textures.addArea("Larry_fin_big_right",sf::IntRect(0,0,128,128));
    textures.addArea("Larry_fin_tiny_left",sf::IntRect(256,64,64,64));
    textures.addArea("Larry_fin_tiny_right",sf::IntRect(256,0,64,64));
    textures.addArea("Larry_tail",sf::IntRect(128,0,128,256));

    testTextures.addTexture("../data/Default.png");
    testTextures.addArea("Larry_eye",sf::IntRect(768,192,64,64));
    testTextures.addArea("Larry_mouth",sf::IntRect(832,0,128,128));
    testTextures.addArea("Larry_fin_big_left",sf::IntRect(512,128,128,128));
    testTextures.addArea("Larry_fin_big_right",sf::IntRect(512,0,128,128));
    testTextures.addArea("Larry_fin_tiny_left",sf::IntRect(768,64,64,64));
    testTextures.addArea("Larry_fin_tiny_right",sf::IntRect(768,0,64,64));
    testTextures.addArea("Larry_tail",sf::IntRect(640,0,128,256));

    texts.addFont("Roboto", "../data/Roboto-Regular.ttf");

    fish.setTexture(textures.get().texture);
    fish.setTextureAreas(textures.get().areas);
    testFish.setTexture(testTextures.get().texture);
    testFish.setTextureAreas(testTextures.get().areas);

    fish.init();
    testFish.init();
      // start main loop
    while(App.isOpen())
    {
      // process events
      sf::Event event;
       while (App.pollEvent(event)) {
          switch (event.type) {
              case sf::Event::Closed:
                  App.close();
              case sf::Event::KeyPressed:
                  if (event.key.code == sf::Keyboard::Escape)
                      App.close();
                  else if (event.key.code == sf::Keyboard::Num1)
                      music.play("canary");
                  else if (event.key.code == sf::Keyboard::Num2)
                      music.play("orchestral");
                  else if (event.key.code == sf::Keyboard::Num3)
                      music.play("ding");
                  else if (event.key.code == sf::Keyboard::P)
                      music.stop();
                  else if(event.key.code == sf::Keyboard::Space)
                     isTest = !isTest;
              default:
                  break;
          }
         
      }

      // clear screen and fill with blue
      App.clear(sf::Color::Blue);

      sf::Vector2i mousePos=sf::Mouse::getPosition(App);
      fish.swimTo(sf::Vector2f(mousePos.x,mousePos.y));
      testFish.swimTo(sf::Vector2f(mousePos.x,mousePos.y));

      // test font
      sf::Text testText;
      testText.setFont(*(texts.getFont("Roboto")));
      testText.setColor(sf::Color::Green);
      testText.setString("TEST");
      testText.setPosition(50,50);
      testText.setCharacterSize(40);

      /*(texts.get("asdf"))->setString("TEST");
      (texts.get("asdf"))->setPosition(50,50);

      App.draw(*(texts.get("asdf")));*/

      if(isTest) {
        App.draw(testFish);
        testText.setString("Test Fish");
      }
      else {
        App.draw(fish);
        testText.setString("Larry");
      }

      App.draw(testText);
      //App.draw(fish);
      // display
      App.display();
    }

    // Done.
    return 0;
  }
