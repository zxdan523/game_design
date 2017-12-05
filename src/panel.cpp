/**
panel.cpp
Class file for the panel class
CSCI 437
@author Stephen Tung
*/
#pragma once
#include "panel.h"
#include <cstdlib>

using namespace sf;

ui::Panel::Panel(const Vector2f& size, const std::string& title, const Font& pFont)
{
  _font = pFont;

  _title.setFont(_font);
  _title.setCharacterSize(24);
  _title.setFillColor(TEXT_COLOR);
  _title.setString(title);
  _title.setOrigin(_title.getGlobalBounds().width / 2, _title.getGlobalBounds().height / 2);
  _title.setPosition(0.0f, size.y - (size.y * 1.4));
  
  _shape = RectangleShape(size);
  _shape.setFillColor(PANEL_COLOR);
  _shape.setOrigin(_shape.getGlobalBounds().width / 2, _shape.getGlobalBounds().height / 2);
}

std::shared_ptr<ui::Button> ui::Panel::addButton(const Button& btn, const Vector2f& pos)
{
	std::shared_ptr<ui::Button> btn_ptr = std::make_shared<ui::Button>(btn);
	btn_ptr->setPosition(pos);
	_btns.push_back(btn_ptr);
	_btns[0]->unselected();
	return btn_ptr;
}

void ui::Panel::update(float mouseX, float mouseY)
{
	for (int i = 0; i != _btns.size(); i++)
	{
		_btns[i]->update(mouseX, mouseY);
	}
}

std::string ui::Panel::select(float mouseX, float mouseY)
{
	for (int i = 0; i != _btns.size(); i++)
	{
		if (_btns[i]->select(mouseX, mouseY) != "None")
			return _btns[i]->select(mouseX, mouseY);
	}
	return "None";
}

void ui::Panel::draw(RenderTarget& target, RenderStates states) const
{
	states.transform*=getTransform();
	target.draw(_shape, states);
	target.draw(_title, states);
	for (auto i = _btns.begin(); i != _btns.end(); i++)
	{
		target.draw(*(*i), states);
	}
}
