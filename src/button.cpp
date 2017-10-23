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

ui::Button::Button(std::string str, std::string id, Font& bFont, Vector2f location)
{
	buttonID = id;
	font = bFont;
	position = location;
	text.setString(str);
	text.setFont(bFont);
	text.setOrigin(float(text.getGlobalBounds().width / 2), float(text.getGlobalBounds().height / 2));
	text.setColor(normalText);
	borderRadius = 5.f;
	borderThickness = 0.f;
	size = Vector2f(text.getGlobalBounds().width * 1.5f, text.getGlobalBounds().height * 1.5f);
	buttonShape = RectangleShape(size);
	Vector2f textPos = Vector2f(buttonShape.getPosition().x, buttonShape.getPosition().y - buttonShape.getGlobalBounds().height / 4);
	text.setPosition(textPos);
}

void Button::setTextColorNormal(Color nButtonText) {
	normalText = nButtonText;
}

void Button::Button::setTextColorClick(Color cButtonText) {
	clickText = cButtonText;
}

void Button::Button::setColorNormal(Color nbg)
{
	normalBackground = nbg;
}

void Button::Button::setColorClick(Color cbg)
{
	clickBackground = cbg;
}

void Button::Button::setColorBorder(Color borderColor)
{
	border = borderColor;
}

void Button::Button::setBorderThickness(float thickness)
{
	borderThickness = thickness;
}

void Button::Button::setBorderRadius(float radius)
{
	borderRadius = radius;
}

void Button::setPosition(Vector2f pos)
{
	position = pos;
}

void Button::setSize(unsigned int bSize)
{
	fontSize = bSize;
	text.setCharacterSize(fontSize);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	size = Vector2f(text.getGlobalBounds().width * 1.5f, text.getGlobalBounds().height + text.getGlobalBounds().height * 1.5f);
	buttonShape = RectangleShape(size);
}

void Button::setText(std::string str)
{
	text.setString(str);
}

void Button::setID(std::string str)
{
	buttonID = str;
}

void Button::setFont(Font& bFont)
{
	font = bFont;
}

Vector2f Button::getPosition()
{
	return position;
}

Vector2f Button::getDimensions()
{
	return Vector2f(buttonShape.getGlobalBounds().width, buttonShape.getGlobalBounds().height);
}

Uint32 Button::getState()
{
	return state;
}

void Button::update(Event& e, RenderWindow window)
{
	Vector2i mousePos = Mouse::getPosition(window);


	bool mouseOnButton = mousePos.x >= buttonShape.getPosition().x - buttonShape.getGlobalBounds().width / 2 && \
						 mousePos.x <= buttonShape.getPosition().x + buttonShape.getGlobalBounds().width / 2 && \
						 mousePos.y >= buttonShape.getPosition().y - buttonShape.getGlobalBounds().height / 2 && \
						 mousePos.y <= buttonShape.getPosition().y + buttonShape.getGlobalBounds().height / 2;

  if (e.type == Event::MouseButtonPressed)
  {
    if (e.mouseButton.button == Mouse::Left)
    {
      if(mouseOnButton)
      {
        buttonShape.setFillColor(clickBackground);
        buttonText.setColor(clickText);
      }
      else
      buttonShape.setFillColor(normalBackground);
      buttonText.setColor(normalText);
    }
  }
}

void draw(RenderTarget& target, RenderStates states) const
{
  target.draw(buttonShape, states);
  target.draw(text, states);
}
