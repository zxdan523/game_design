#include <SFML/Graphics.hpp>
#include "Larry.h"
//#include "ResourceManager.h"
#include "TextureManager.h"
#include "TextManager.h"
#include <iostream>

int main(int argc, char** argv)
{
  //ResourceManager<std::string, sf::Texture> textures;
  //ResourceManager<std::string, sf::Font> fonts;

  TextureManager textures;
  TextManager texts;

  //textures.loadResource("Larry", "../data/Larry.png");
  //fonts.loadResource("asdf", "../data/Roboto-Regular.ttf");
  

  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);
    Larry fish;
    /*Note: to save the memory fot passing texture and texture location, I used shared pointer. However, shared pointer can only be created dynamically, so you need to use make_shared<T>, or you will have segementation fault*/
    //std::shared_ptr<sf::Texture> texture=std::make_shared<sf::Texture>();
    //texture->loadFromFile("../data/Larry.png");
    //fish.setTexture(texture);
    //fish.setTexture(textures.getResource("Larry"));
    
    //std::cout << textures.getResource("Larry").use_count()<<std::endl;
    textures.addTexture("../data/Default.png"); 
    textures.addArea("Larry_eye",sf::IntRect(256,192,64,64));
    textures.addArea("Larry_mouth",sf::IntRect(320,0,128,128));
    textures.addArea("Larry_fin_big_left",sf::IntRect(0,128,128,128));
    textures.addArea("Larry_fin_big_right",sf::IntRect(0,0,128,128));
    textures.addArea("Larry_fin_tiny_left",sf::IntRect(256,64,64,64));
    textures.addArea("Larry_fin_tiny_right",sf::IntRect(256,0,64,64));
    textures.addArea("Larry_tail",sf::IntRect(128,0,128,256));

    texts.addFont("Roboto", "../data/Roboto-Regular.ttf");

    /*fish.setTexture(textures.get("Larry").texture);
    fish.setTextureAreas(textures.get("Larry").areas);*/

    fish.setTexture(textures.get("Shark").texture);
    fish.setTextureAreas(textures.get("Shark").areas);

    fish.init();
    // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        App.close();
    }

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

    sf::Vector2i mousePos=sf::Mouse::getPosition(App);
    fish.swimTo(sf::Vector2f(mousePos.x,mousePos.y));

    // test font
    sf::Text testText;
    testText.setFont(*(texts.getFont("Roboto")));
    testText.setColor(sf::Color::Green);
    testText.setString("TEST");
    testText.setPosition(50,50);
    testText.setCharacterSize(40);


    textures.addArea("Larry_eye",sf::IntRect(256,192,64,64));
    textures.addArea("Larry_mouth",sf::IntRect(320,0,128,128));
    textures.addArea("Larry_fin_big_left",sf::IntRect(0,128,128,128));
    textures.addArea("Larry_fin_big_right",sf::IntRect(0,0,128,128));
    textures.addArea("Larry_fin_tiny_left",sf::IntRect(256,64,64,64));
    textures.addArea("Larry_fin_tiny_right",sf::IntRect(256,0,64,64));
    textures.addArea("Larry_tail",sf::IntRect(128,0,128,256));

    /*(texts.get("asdf"))->setString("TEST");
    (texts.get("asdf"))->setPosition(50,50);

    App.draw(*(texts.get("asdf")));*/
    App.draw(testText);
    App.draw(fish);
    // display
    App.display();
  }

  // Done.
  return 0;
}
