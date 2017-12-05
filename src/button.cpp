/**
button.cpp
Class file for the button class
CSCI 437
@author Stephen Tung
*/
#pragma once
#include "button.h"
#include <cstdlib>

using namespace sf;

ui::Button::Button(const std::string& label, const Font& bFont, const Vector2f& size)
{
	_state = ui::state::unselected;
	
	_text.setString(label);
	_text.setFont(bFont);
	_text.setCharacterSize(size.y / 2.0f);
	_text.setColor(TEXT_COLOR);
	_text.setOrigin(float(_text.getGlobalBounds().width / 2), float(_text.getGlobalBounds().height / 2));
	
	Vector2f buttonSize = Vector2f(float(_text.getGlobalBounds().width) * 1.5f, float(_text.getGlobalBounds().height) * 1.5f);
	_shape = RectangleShape(buttonSize);
	_shape.setFillColor(UNSELECTED_COLOR);
	_shape.setOrigin(_shape.getGlobalBounds().width / 2, _shape.getGlobalBounds().height / 2);

	Vector2f textPos = Vector2f(_shape.getPosition().x, _shape.getPosition().y - _shape.getGlobalBounds().height / 4);
	_text.setPosition(textPos);
}

ui::Button::Button(const Button& btn)
{
	_text = btn._text;
	_shape = btn._shape;
}

ui::Button& ui::Button::operator=(const Button& btn)
{
	_text = btn._text;
	_shape = btn._shape;
	return *this;
}

void ui::Button::setPosition(Vector2f pos)
{
	_shape.setPosition(pos);
	Vector2f textPos = Vector2f(_shape.getPosition().x, _shape.getPosition().y - _shape.getGlobalBounds().height / 4);
	_text.setPosition(textPos);
}

void ui::Button::unselected()
{
	_state = ui::state::unselected;
	_shape.setFillColor(UNSELECTED_COLOR);
	_text.setFillColor(TEXT_COLOR);
}

void ui::Button::hover()
{
	_state = ui::state::hover;
	_shape.setFillColor(HOVER_COLOR);
	_text.setFillColor(TEXT_COLOR);
}

void ui::Button::selected()
{
	_state = ui::state::selected;
	_shape.setFillColor(SELECTED_COLOR);
	_text.setFillColor(TEXT_COLOR);
}

bool ui::Button::mouseInButton(float mouseX, float mouseY)
{
	_mouseInButton = mouseX >= _shape.getPosition().x - _shape.getGlobalBounds().width / 2
		&& mouseX <= _shape.getPosition().x + _shape.getGlobalBounds().width / 2
		&& mouseY >= _shape.getPosition().y - _shape.getGlobalBounds().height / 2
		&& mouseY <= _shape.getPosition().y + _shape.getGlobalBounds().height / 2;

	return _mouseInButton;
}

void ui::Button::update(float mouseX, float mouseY)
{
	if (mouseInButton(mouseX, mouseY) == true)
	{
		hover();
	}
	else
		unselected();
}

std::string ui::Button::select(float mouseX, float mouseY)
{
	if (mouseInButton(mouseX, mouseY) == true)
	{
		selected();
		return _text.getString();
	}
	else
	{
		unselected();
	}
	return "None";
}

void ui::Button::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(_shape, states);
	target.draw(_text, states);
}