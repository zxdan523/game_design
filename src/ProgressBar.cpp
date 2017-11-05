/**
ProgressBar.cpp
Class file for the ProgressBar class
CSCI 437
@author Stephen Tung
*/
#pragma once
#include "ProgressBar.h"
#include <cstdlib>

using namespace sf;

ui::ProgressBar::ProgressBar(float width)
{
	Vector2f barSize = Vector2f(width, height);
	barShape = RectangleShape(barSize);

}

void ui::ProgressBar::setValue(float val)
{
	value = val;
}

float ui::ProgressBar::getValue() const
{
	return value;
}

void ui::ProgressBar::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(barShape, states);

}