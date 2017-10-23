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

class Button : public Drawable
{
public:
  Button(std::string str, std::string id, Color usColor, Color selColor, Color txtColor, Font& bFont, Vector2f pos);
  void selected();
  void unselected();

private:
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

#endif
