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
			hover = 1,
			selected = 2
		};
	};
	class Button : public Drawable, public Transformable
	{
	public:
		Button();
		Button(std::string str, std::string id, Color usColor, Color hovColor, Color selColor, Color txtColor, Font& bFont, Vector2f pos);
		void unselected();
		void hover();
		void selected();
		bool mouseInButton(Event& e, RenderWindow& window);
		void update(Event& e, RenderWindow& window);

		void setUnselectedColor(Color uColor);
		void setHoverColor(Color hColor);
		void setSelectedColor(Color sColor);
		void setTextColor(Color tColor);
		Color getUnselectedColor();
		Color getHoverColor();
		Color getSelectedColor();
		Color getTextColor();
		RectangleShape getButtonShape();
		Uint32 getButtonState();
		std::string getButtonID();

	private:
		Uint32 buttonState;
		Color unselectedColor;
		Color hoverColor;
		Color selectedColor;
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
