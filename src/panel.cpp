/**
panel.cpp
Class file for the panel class
CSCI 437
@author Stephen Tung
*/
#pragma once
#include "Panel.h"
#include <cstdlib>

using namespace sf;

ui::Panel::Panel()
{
	panelPosition = sf::Vector2f(400.f, 300.f);
	panelSize = sf::Vector2f(400.f, 400.f);
	panelColor = Color(100, 100, 100, 180);

	panelShape = RectangleShape(panelSize);
	panelShape.setFillColor(panelColor);
	panelShape.setOrigin(float(panelShape.getGlobalBounds().width / 2), float(panelShape.getGlobalBounds().height / 2));
	panelShape.setPosition(panelPosition);
}

ui::Panel::Panel(Vector2f pos, Vector2f size, Color color)
{
  panelPosition = pos;
  panelSize = size;
  panelColor = color;
  
  panelShape = RectangleShape(panelSize);
  panelShape.setFillColor(panelColor);
  panelShape.setOrigin(float(panelShape.getGlobalBounds().width / 2), float(panelShape.getGlobalBounds().height / 2));
  panelShape.setPosition(panelPosition);
}

void ui::Panel::addButton(std::string str, std::string id, Color usColor, Color hovColor, Color selColor, Color txtColor, Font& bFont, Vector2f buttonPos)
{
	relButtonPos = buttonPos;
	ui::Button newButton(str, id, usColor, hovColor, selColor, txtColor, bFont, relButtonPos);
	_btns.push_back(newButton);
	//buttonList[id] = newButton;
}

void ui::Panel::removeButton(std::string bID)
{
	//_btns.erase(std::remove(_btns.begin(), _btns.end(), bID), _btns.end());
	//buttonList.erase(bID);
}

ui::Button ui::Panel::getButton(int index)
{
	std::vector<Button>::const_iterator it;
	int i = 0;
	for (it = _btns.begin(); it != _btns.end(); it++, i++)
	{
		if (i == index)
		{
			return *it;
		}
	}
}

void ui::Panel::update(Event& e, RenderWindow& window)
{
	std::vector<Button>::const_iterator it;
	Button button;
	for (it = _btns.begin(); it != _btns.end(); it++)
	{
		button = Button(*it);
		button.update(e, window);
	}
}

void ui::Panel::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(panelShape, states);
	std::vector<Button>::const_iterator it;
	for (it = _btns.begin(); it != _btns.end(); it++)
	{
		target.draw(*it, states);
	}
}
