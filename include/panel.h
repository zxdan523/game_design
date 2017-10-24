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

class Panel : public Drawable, public Transformable
{
public:
	Panel();
	Panel(Vector2f pos);
	void addButton();
	void removeButton(std::string bID);

	static std::map<std::string, ui::Button> buttonList;

private:
  Vector2f panelPosition;
  Vector2f panelSize;
};

#endif
