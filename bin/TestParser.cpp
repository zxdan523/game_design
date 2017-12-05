#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Larry.h"
#include "TextureManager.h"
#include "TerrainManager.h"
#include "TextManager.h"
#include "MusicManager.h"
#include "XMLParser.h"
#include "LevelInfo.h"
#include "tinyxml2.h"
#include <iostream>

int main(int argc, char** argv)
{

  // Resource Managers
	TextureManager textures;
	//TextManager texts;
	std::string a;
	XMLParser parser;
	LevelInfo level;
	TerrainManager terrain;

	parser.loadXML("../data/xml/levels.xml");
	parser.loadTexture(textures);
	parser.setSwordfishInfoList();
	
	parser.loadLevel(level, 1);
	std::cout<<"level: "<<level.getLevelNumber()<<std::endl;
	std::cout<<"length: "<<level.getLevelLength()<<std::endl;
	std::cout<<"minion number: "<<level.getMinionNumber()<<std::endl;
	std::cout<<"bg music: "<<level.getBackgroundMusic()<<std::endl;
	std::cout<<"bg image: "<<level.getBackgroundImage()<<std::endl;
	std::cout<<"terrain 1st point: "<<level.getTerrain()[0][0].y<<std::endl;
	std::cout<<"swordfish "<<parser.getSwordfishInfoList()[4].getSwordfishList()[0].delay<<parser.getSwordfishInfoList()[4].getSwordfishList()[0].pos_y<<std::endl;	

	parser.loadLevel(level, 2);
	std::cout<<"level: "<<level.getLevelNumber()<<std::endl;
	std::cout<<"length: "<<level.getLevelLength()<<std::endl;
	std::cout<<"minion number: "<<level.getMinionNumber()<<std::endl;
	std::cout<<"bg music: "<<level.getBackgroundMusic()<<std::endl;
	std::cout<<"bg image: "<<level.getBackgroundImage()<<std::endl;
	std::cout<<"terrain 1st point: "<<level.getTerrain()[0][0].y<<std::endl;

	parser.loadLevel(level, 3);
	std::cout<<"level: "<<level.getLevelNumber()<<std::endl;
	std::cout<<"length: "<<level.getLevelLength()<<std::endl;
	std::cout<<"minion number: "<<level.getMinionNumber()<<std::endl;
	std::cout<<"bg music: "<<level.getBackgroundMusic()<<std::endl;
	std::cout<<"bg image: "<<level.getBackgroundImage()<<std::endl;
	std::cout<<"terrain 1st point: "<<level.getTerrain()[0][0].y<<std::endl;

	parser.loadLevel(level, 4);
	std::cout<<"level: "<<level.getLevelNumber()<<std::endl;
	std::cout<<"length: "<<level.getLevelLength()<<std::endl;
	std::cout<<"minion number: "<<level.getMinionNumber()<<std::endl;
	std::cout<<"bg music: "<<level.getBackgroundMusic()<<std::endl;
	std::cout<<"bg image: "<<level.getBackgroundImage()<<std::endl;
	std::cout<<"terrain 1st point: "<<level.getTerrain()[0][0].y<<std::endl;

	parser.loadLevel(level, 5);
	std::cout<<"level: "<<level.getLevelNumber()<<std::endl;
	std::cout<<"length: "<<level.getLevelLength()<<std::endl;
	std::cout<<"minion number: "<<level.getMinionNumber()<<std::endl;
	std::cout<<"bg music: "<<level.getBackgroundMusic()<<std::endl;
	std::cout<<"bg image: "<<level.getBackgroundImage()<<std::endl;
	std::cout<<"terrain 1st point: "<<level.getTerrain()[0][0].y<<std::endl;

	terrain.load(level.getTerrain(), sf::Color::Green);

  // create main window
	sf::RenderWindow App(sf::VideoMode(1024,768,32), "XML Test",sf::Style::Titlebar|sf::Style::Close);
	Larry fish;

	//texts.addFont("Roboto", "../data/Roboto-Regular.ttf");

	fish.setTexture(textures.get().texture);
	fish.setTextureAreas(textures.get().areas);
	
	fish.init();
    
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
				default:
				break;
			}

		}

    // clear screen and fill with blue
		App.clear(sf::Color::Blue);

		sf::Vector2i mousePos=sf::Mouse::getPosition(App);
		fish.swimTo(sf::Vector2f(mousePos.x,mousePos.y));
		fish.update(0);

    // test font
		/*sf::Text testText;
		testText.setFont(*(texts.getFont("Roboto")));
		testText.setColor(sf::Color::Green);
		testText.setString("TEST");
		testText.setPosition(50,50);
		testText.setCharacterSize(40);*/
		
		App.draw(terrain);
		App.draw(fish);
		//App.draw(testText);
    // display
		App.display();
	}

  // Done.
	return 0;
}
