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
	buttonPosition = pos;
	buttonState = ui::state::unselected;
	buttonID = id;
	font = bFont;
	unselectedColor = usColor;
	selectedColor = selColor;
	textColor = txtColor;
	buttonText.setString(str);
	buttonText.setFont(bFont);
	buttonText.setOrigin(float(buttonText.getGlobalBounds().width / 2), float(buttonText.getGlobalBounds().height / 2));
	buttonText.setColor(textColor);
	buttonSize = Vector2f(buttonText.getGlobalBounds().width * 1.5f, buttonText.getGlobalBounds().height * 1.5f);
	buttonShape = RectangleShape(buttonSize);
	buttonShape.setFillColor(unselectedColor);
	buttonShape.setOrigin(buttonShape.getGlobalBounds().width / 2, buttonShape.getGlobalBounds().height / 2);
	buttonShape.setPosition(buttonPosition);
	Vector2f textPos = Vector2f(buttonShape.getPosition().x, buttonShape.getPosition().y - buttonShape.getGlobalBounds().height / 4);
	buttonText.setPosition(textPos);
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
	target.draw(buttonText, states);
}
