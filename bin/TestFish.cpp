#include <SFML/Graphics.hpp>
#include "Larry.h"
#include <iostream>
#include "uimanager.h"
#include "button.h"
#include "panel.h"
#include "ProgressBar.h"

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

	sf::Font buttonTextFont;
	buttonTextFont.loadFromFile("Amender_Tu.ttf");

	ui::Button button("Start", "startButton", Color(125, 230, 240), Color(200, 250, 255), Color(), buttonTextFont, sf::Vector2f(400.f, 200.f));

	ui::Button button2("Quit", "quitButton", Color(200, 190, 160), Color(255, 250, 200), Color(), buttonTextFont, sf::Vector2f(400.f, 400.f));

	//ui::ProgressBar progressBar(sf::Vector2f(400.f, 300.f), 100.f, 0.0f);

    // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {
		if (Event.type == sf::Event::MouseButtonPressed)
		{
			if (button.mouseInButton(Event, App) == true)
				button.selected();
			else if (button2.mouseInButton(Event, App) == true)
				button2.selected();
		}
		else if (Event.type == sf::Event::MouseButtonReleased)
		{
			button.unselected();
			button2.unselected();
		}
		      // Exit
      if(Event.type == sf::Event::Closed)
		  App.close();
    }
	
    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

	App.draw(button);
	App.draw(button2);

    /*
	sf::Vector2i mousePos=sf::Mouse::getPosition(App);
    fish.swimTo(sf::Vector2f(mousePos.x,mousePos.y));
    App.draw(fish);
	*/
    // display
    App.display();
  }

  // Done.
  return 0;
}
