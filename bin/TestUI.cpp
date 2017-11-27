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
    
	sf::Font buttonTextFont;
	buttonTextFont.loadFromFile("Amender_Tu.ttf");

	ui::Panel panel1(sf::Vector2f(400.f, 300.f), sf::Vector2f(400.f, 400.f), Color(100, 100, 100, 180));

	panel1.addButton("Start", "startButton", Color(125, 230, 240), Color(150, 240, 245), Color(200, 250, 255), Color(), buttonTextFont, sf::Vector2f(400.f, 200.f));
	ui::Button button1 = panel1.getButton(0);

	panel1.addButton("Quit", "quitButton", Color(200, 190, 160), Color(230, 230, 180), Color(255, 250, 200), Color(), buttonTextFont, sf::Vector2f(400.f, 400.f));
	ui::Button quitButton = panel1.getButton(1);

	//ui::Button button("Start", "startButton", Color(125, 230, 240), Color(150, 240, 245), Color(200, 250, 255), Color(), buttonTextFont, sf::Vector2f(400.f, 200.f));

	//ui::Button quitButton("Quit", "quitButton", Color(200, 190, 160), Color(230, 230, 180), Color(255, 250, 200), Color(), buttonTextFont, sf::Vector2f(400.f, 400.f));

	//ui::ProgressBar progressBar(sf::Vector2f(400.f, 300.f), 100.f, 0.0f);

    // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
	while (App.pollEvent(Event))
	{
		//button.update(Event, App);
		panel1.update(Event, App);
		button1.update(Event, App);
		quitButton.update(Event, App);

		// Exit
		if (Event.type == sf::Event::Closed)
			App.close();
		if (quitButton.getButtonState() == ui::state::selected)
			App.close();
		//if (button1.getButtonState() == ui::state::selected)
			//App.close();
	}
	
    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

	//App.draw(button);
	//App.draw(quitButton);
	App.draw(panel1);

    // display
    App.display();
  }

  // Done.
  return 0;
}
