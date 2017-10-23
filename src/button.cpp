/**
button.cpp
Class file for the button class
CSCI 437
@author Stephen Tung
*/
#pragma once
#include "Button.h"
#include <cstdlib>

using namespace sf;

ui::Button::Button()
{

}

ui::Button::Button(std::string str, std::string id, Color usColor, Color selColor, Color txtColor, Font& bFont, Vector2f pos)
{
	position = pos;
	buttonState = ui::state::unselected;
	buttonID = id;
	font = bFont;
  unselectedColor = usColor;
  selectedColor = selColor;
  textColor = txtColor;
	text.setString(str);
	text.setFont(bFont);
	text.setOrigin(float(text.getGlobalBounds().width / 2), float(text.getGlobalBounds().height / 2));
	text.setColor(textColor);
	size = Vector2f(text.getGlobalBounds().width * 1.5f, text.getGlobalBounds().height * 1.5f);
	buttonShape = RectangleShape(size);
	buttonShape.setFillColor(unselectedColor);
	Vector2f textPos = Vector2f(buttonShape.getPosition().x, buttonShape.getPosition().y - buttonShape.getGlobalBounds().height / 4);
	text.setPosition(textPos);
}

void ui::Button::selected()
{
	buttonState = ui::state::selected;
	buttonShape.setFillColor(selectedColor);
  buttonText.setColor(textColor);
}

void ui::Button::unselected()
{
	buttonState = ui::state::unselected;
  buttonShape.setFillColor(unselectedColor);
  buttonText.setColor(textColor);
}

void ui::Button::draw(RenderTarget& target, RenderStates states) const
{
  target.draw(buttonShape, states);
  target.draw(text, states);
}
