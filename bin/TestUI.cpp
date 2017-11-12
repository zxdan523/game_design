#include <SFML/Graphics.hpp>
#include <iostream>
#include "uimanager.h"
#include "button.h"
#include "panel.h"
#include "ProgressBar.h"

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);
    
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
		if (Event.type == sf::Event::MouseButtonPressed)
		{
			if (button.mouseInButton(Event, App) == true)
			{
				button.selected();
			}
		}
		else if (Event.type == sf::Event::MouseButtonReleased)
		{
			if (button.mouseInButton(Event, App) == true)
			{
				button.hover();
			}
			else
				button.unselected();
		}
		else
		{ 
			if (button.mouseInButton(Event, App) == true)
			{
				button.hover();
			}
			else
				button.unselected();
		}

		if (Event.type == sf::Event::MouseButtonPressed)
		{
			if (quitButton.mouseInButton(Event, App) == true)
			{
				quitButton.selected();
			}
		}
		else if (Event.type == sf::Event::MouseButtonReleased)
		{
			if (quitButton.mouseInButton(Event, App) == true)
			{
				quitButton.hover();
			}
			else
				quitButton.unselected();
		}
		else
		{
			if (quitButton.mouseInButton(Event, App) == true)
			{
				quitButton.hover();
			}
			else
				quitButton.unselected();
		}
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
