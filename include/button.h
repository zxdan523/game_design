/**
button.h
Header file for the button class
CSCI 437
@author Stephen Tung
*/
#ifndef BUTTON_H
#define BUTTON_H
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
namespace ui
{
	namespace state
	{
		enum
		{
			unselected = 0,
			selected = 1
		};
	};
	class Button : public Drawable, public Transformable
	{
	public:
		Button();
		Button(std::string str, std::string id, Color usColor, Color selColor, Color txtColor, Font& bFont, Vector2f pos);
		void selected();
		void unselected();
		void remove(std::string bID);
		RectangleShape getButtonShape();

	private:
		Uint32 buttonState;
		Color selectedColor;
		Color unselectedColor;
		Color textColor;
		RectangleShape buttonShape;
		Vector2f buttonPosition;
		Vector2f buttonSize;
		Font font;
		unsigned int fontSize;
		std::string buttonID;
		Text buttonText;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}
#endif
