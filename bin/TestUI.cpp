#include <SFML/Graphics.hpp>
#include <iostream>
#include "uimanager.h"
#include "button.h"
#include "panel.h"
#include "ProgressBar.h"

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Larry, Swim!",sf::Style::Titlebar|sf::Style::Close);
    
	sf::Font buttonTextFont;
	buttonTextFont.loadFromFile("Amender_Tu.ttf");

	ui::Button button("Start", "startButton", Color(125, 230, 240), Color(150, 240, 245), Color(200, 250, 255), Color(), buttonTextFont, sf::Vector2f(400.f, 200.f));

	ui::Button quitButton("Quit", "quitButton", Color(200, 190, 160), Color(230, 230, 180), Color(255, 250, 200), Color(), buttonTextFont, sf::Vector2f(400.f, 400.f));

	//ui::ProgressBar progressBar(sf::Vector2f(400.f, 300.f), 100.f, 0.0f);

    // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
	while (App.pollEvent(Event))
	{
		button.update(Event, App);
		quitButton.update(Event, App);

		// Exit
		if (Event.type == sf::Event::Closed)
			App.close();
		if (quitButton.getButtonState() == ui::state::selected)
			App.close();
	}
	
    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

	App.draw(button);
	App.draw(quitButton);

    // display
    App.display();
  }

  // Done.
  return 0;
}
