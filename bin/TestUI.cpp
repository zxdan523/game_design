#include <SFML/Graphics.hpp>
#include <iostream>
#include "uimanager.h"
#include "button.h"
#include "panel.h"
#include "ProgressBar.h"

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "FISHNAPPED",sf::Style::Titlebar|sf::Style::Close);
    
	sf::Font textFont;
	textFont.loadFromFile("Amender_Tu.ttf");

	ui::Panel panel = ui::Panel(Vector2f(400.0f, 400.0f), "Test Panel", textFont);
	ui::Button button1 = ui::Button("Start", textFont, Vector2f(100.0f, 50.0f));
	panel.setPosition(400.0f, 300.0f);
	panel.addButton(button1, Vector2f(0.0f, -100.0f));

	button1.setPosition(Vector2f(400.0f, 400.0f));

    // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
	while (App.pollEvent(Event))
	{
		Vector2i mousePos = Mouse::getPosition(App);
		Vector2f mousePosition = Vector2f(mousePos);

		panel.update(mousePosition.x, mousePosition.y);
		button1.update(mousePosition.x, mousePosition.y);

		// Exit
		if (Event.type == sf::Event::Closed)
			App.close();
		if (Event.type == sf::Event::MouseButtonPressed)
		{
			if (panel.select(mousePosition.x, mousePosition.y) == "Start")
			{
				App.close();
			}			
		}
	}
	
    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

	App.draw(panel);
	//draw(button1);

    // display
    App.display();
  }

  // Done.
  return 0;
}
