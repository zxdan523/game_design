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
	buttonPosition = Vector2f(400.f, 300.f);
	buttonState = ui::state::unselected;
	font.loadFromFile("Amender_Tu.ttf");

	buttonText.setFont(font);
	buttonText.setOrigin(float(buttonText.getGlobalBounds().width / 2), float(buttonText.getGlobalBounds().height / 2));
	buttonText.setColor(textColor);

	buttonSize = Vector2f(float(buttonText.getGlobalBounds().width) * 1.5f, float(buttonText.getGlobalBounds().height) * 1.5f);
	buttonShape = RectangleShape(buttonSize);
	buttonShape.setFillColor(unselectedColor);
	buttonShape.setOrigin(buttonShape.getGlobalBounds().width / 2, buttonShape.getGlobalBounds().height / 2);
	buttonShape.setPosition(buttonPosition);

	Vector2f textPos = Vector2f(buttonShape.getPosition().x, buttonShape.getPosition().y - buttonShape.getGlobalBounds().height / 4);
	buttonText.setPosition(textPos);
}

ui::Button::Button(std::string str, std::string id, Color usColor, Color hovColor, Color selColor, Color txtColor, Font& bFont, Vector2f pos)
{
	buttonPosition = pos;
	buttonState = ui::state::unselected;
	buttonID = id;
	font = bFont;
	setUnselectedColor(usColor);
	setHoverColor(hovColor);
	setSelectedColor(selColor);
	setTextColor(txtColor);

	buttonText.setString(str);
	buttonText.setFont(bFont);
	buttonText.setOrigin(float(buttonText.getGlobalBounds().width / 2), float(buttonText.getGlobalBounds().height / 2));
	buttonText.setColor(txtColor);

	buttonSize = Vector2f(float(buttonText.getGlobalBounds().width) * 1.5f, float(buttonText.getGlobalBounds().height) * 1.5f);
	buttonShape = RectangleShape(buttonSize);
	buttonShape.setFillColor(usColor);
	buttonShape.setOrigin(buttonShape.getGlobalBounds().width / 2, buttonShape.getGlobalBounds().height / 2);
	buttonShape.setPosition(buttonPosition);

	Vector2f textPos = Vector2f(buttonShape.getPosition().x, buttonShape.getPosition().y - buttonShape.getGlobalBounds().height / 4);
	buttonText.setPosition(textPos);
}

void ui::Button::setUnselectedColor(Color uColor)
{
	unselectedColor = uColor;
}

Color ui::Button::getUnselectedColor()
{
	return unselectedColor;
}

void ui::Button::setHoverColor(Color hColor)
{
	hoverColor = hColor;
}

Color ui::Button::getHoverColor()
{
	return hoverColor;
}

void ui::Button::setSelectedColor(Color sColor)
{
	selectedColor = sColor;
}

Color ui::Button::getSelectedColor()
{
	return selectedColor;
}

void ui::Button::setTextColor(Color tColor)
{
	textColor = tColor;
}

Color ui::Button::getTextColor()
{
	return textColor;
}

void ui::Button::unselected()
{
	buttonState = ui::state::unselected;
	buttonShape.setFillColor(getUnselectedColor());
	buttonText.setColor(getTextColor());
}

void ui::Button::hover()
{
	buttonState = ui::state::hover;
	buttonShape.setFillColor(getHoverColor());
	buttonText.setColor(getTextColor());
}

void ui::Button::selected()
{
	buttonState = ui::state::selected;
	buttonShape.setFillColor(getSelectedColor());
	buttonText.setColor(getTextColor());
}


void ui::Button::remove(std::string bID)
{

}

RectangleShape ui::Button::getButtonShape()
{
	return buttonShape;
}

Uint32 ui::Button::getButtonState()
{
	return buttonState;
}

void ui::Button::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(buttonShape, states);
	target.draw(buttonText, states);
}

bool ui::Button::mouseInButton(Event& e, RenderWindow& window)
{
	Vector2i mousePosition = sf::Mouse::getPosition(window);

	bool mouseInButton = mousePosition.x >= buttonShape.getPosition().x - buttonShape.getGlobalBounds().width / 2
		&& mousePosition.x <= buttonShape.getPosition().x + buttonShape.getGlobalBounds().width / 2
		&& mousePosition.y >= buttonShape.getPosition().y - buttonShape.getGlobalBounds().height / 2
		&& mousePosition.y <= buttonShape.getPosition().y + buttonShape.getGlobalBounds().height / 2;

	return mouseInButton;
}

void ui::Button::update(Event& e, RenderWindow& window)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (mouseInButton(e, window) == true)
		{
			selected();
		}
	}
	else if (e.type == Event::MouseButtonReleased)
	{
		if (mouseInButton(e, window) == true)
		{
			hover();
		}
		else
			unselected();
	}
	else
	{
		if (mouseInButton(e, window) == true)
		{
			hover();
		}
		else
			unselected();
	}
}