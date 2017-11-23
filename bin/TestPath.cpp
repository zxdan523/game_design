#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Minions.h"
#include "XMLParser.h"
#include "Larry.h"
#include "TextureManager.h"
#include "TileMap.h"
#include <iostream>
#include "util.h"

sf::Vector2f getPath(sf::Vector2i dest) {
	return sf::Vector2f(dest.x + 100,dest.y + 100);	
}

int main(int argc, char** argv)
{

  // Resource Managers
	TextureManager textures;
	XMLParser parser;
	TileMap map;

  // create main window
	sf::RenderWindow App(sf::VideoMode(1024,768,32), "Path - SFML",sf::Style::Titlebar|sf::Style::Close);
	Minions minion;
	Larry larry;

	parser.loadXML("../data/xml/TestXML.xml");
	parser.loadTexture(textures, "fish");
	std::vector<int> tiles = parser.getTileMap();
	parser.loadTexture(textures,"terrain");
  	if (!map.load(textures,"grass", sf::Vector2u(64, 64), tiles, 16, 12))
    	return -1;


	
	minion.setTexture(textures.get("fish").texture);
	minion.setTextureAreas(textures.get("fish").areas);
	larry.setTexture(textures.get("fish").texture);
	larry.setTextureAreas(textures.get("fish").areas);

	minion.init();
	larry.init();
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
                        minion.recovered();
                    if(event.key.code==sf::Keyboard::S)
                        minion.shot();
                    if(event.key.code==sf::Keyboard::D)
                        minion.shocked();
                    if(event.key.code==sf::Keyboard::F)
                        minion.weaken();
                break;
            default:
                break;
        }
    }
    // clear screen and fill with blue
		App.clear(sf::Color::Blue);
		
		sf::Vector2i mousePos=sf::Mouse::getPosition(App);
		//minion.swimTo(sf::Vector2f(mousePos.x,mousePos.y));
		minion.swimTo(getPath(mousePos));
		minion.update(0);
		larry.swimTo(sf::Vector2f(mousePos.x,mousePos.y));
		larry.update(0);
		App.draw(map);
		App.draw(larry);
		App.draw(minion);
		App.display();
	}


  // Done.
	return 0;

}

