#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Minions.h"
#include "XMLParser.h"
#include "TextureManager.h"
#include <iostream>
#include "util.h"

int main(int argc, char** argv)
{

  // Resource Managers
	TextureManager textures;
	XMLParser parser;


  // create main window
	sf::RenderWindow App(sf::VideoMode(1024,768,32), "Path - SFML",sf::Style::Titlebar|sf::Style::Close);
	Minions fish;

	parser.loadXML("../data/xml/TestXML.xml");
	parser.loadTexture(textures, "fish");

	
	fish.setTexture(textures.get("fish").texture);
	fish.setTextureAreas(textures.get("fish").areas);

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
                        fish.recovered();
                    if(event.key.code==sf::Keyboard::S)
                        fish.shot();
                    if(event.key.code==sf::Keyboard::D)
                        fish.shocked();
                    if(event.key.code==sf::Keyboard::F)
                        fish.weaken();
                break;
            default:
                break;
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
}