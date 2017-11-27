/**
panel.h
Header file for the panel class
CSCI 437
@author Stephen Tung
*/
#ifndef PANEL_H
#define PANEL_H
#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace sf;

namespace ui
{
	class Panel : public Drawable, public Transformable
	{
	public:
		Panel();
		Panel(Vector2f pos, Vector2f size, Color color);
		void addButton(std::string str, std::string id, Color usColor, Color hovColor, Color selColor, Color txtColor, Font& bFont, Vector2f pos);
		void removeButton(std::string bID);
		Button getButton(int index);

		void ui::Panel::update(Event& e, RenderWindow& window);

		//static std::map<std::string, Button> buttonList;
		std::vector<Button> _btns;

	private:
		RectangleShape panelShape;
		Color panelColor;
		Vector2f panelPosition;
		Vector2f panelSize;
		Vector2f relButtonPos;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}
#endif
