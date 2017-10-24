#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Larry.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "MusicManager.h"
#include "tinyxml2.h"
#include <iostream>

using namespace tinyxml2;

int main(int argc, char** argv)
{

  // Resource Managers
	TextureManager textures;
	MusicManager music;
	music.add();
	TextManager texts;
	static const char* xml =
		"<?xml version=\"1.0\"?>"
		"<!DOCTYPE PLAY SYSTEM \"play.dtd\">"
		"<PLAY>"
		"<TITLE>A Midsummer Night's Dream</TITLE>"
		"</PLAY>";
	XMLDocument doc;
	doc.Parse( xml );
	XMLElement* titleElement = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE" );
	const char* title = titleElement->GetText();
	printf( "Name of play (1): %s\n", title );

  // create main window
	sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);
	Larry fish;

    /*Note: to save the memory fot passing texture and texture location, I used shared pointer. However, shared pointer can only be created dynamically, so you need to use make_shared<T>, or you will have segementation fault*/
	textures.addTexture("../data/Default.png"); 
	textures.addArea("Larry_eye",sf::IntRect(256,192,64,64));
	textures.addArea("Larry_mouth",sf::IntRect(320,0,128,128));
	textures.addArea("Larry_fin_big_left",sf::IntRect(0,128,128,128));
	textures.addArea("Larry_fin_big_right",sf::IntRect(0,0,128,128));
	textures.addArea("Larry_fin_tiny_left",sf::IntRect(256,64,64,64));
	textures.addArea("Larry_fin_tiny_right",sf::IntRect(256,0,64,64));
	textures.addArea("Larry_tail",sf::IntRect(128,0,128,256));

	texts.addFont("Roboto", "../data/Roboto-Regular.ttf");

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
				else if (event.key.code == sf::Keyboard::Num1)
					music.play("canary");
				else if (event.key.code == sf::Keyboard::Num2)
					music.play("orchestral");
				else if (event.key.code == sf::Keyboard::Num3)
					music.play("ding");
				else if (event.key.code == sf::Keyboard::P)
					music.stop();
				/*else if(event.key.code == sf::Keyboard::Space)
					isTest = !isTest;*/
				default:
				break;
			}

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
		
		App.draw(fish);
		App.draw(testText);
    //App.draw(fish);
    // display
		App.display();
	}

  // Done.
	return 0;
}
