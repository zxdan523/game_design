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

ui::ProgressBar::ProgressBar()
{

}

ui::ProgressBar::ProgressBar(Vector2f pos, float width, float val)
{
	position = pos;
	value = val;
	texture.loadFromFile("../data/progressbartexture.png");
	barTexture = &texture;
	Vector2f barSize = Vector2f(width, height);
	barShape = RectangleShape(barSize);
	barShape.setPosition(position);
	barShape.setTexture(barTexture);
	setValue(value);

}

void ui::ProgressBar::setValue(float val)
{
	value = val;
	
	for (float i = 0; i < val; i++)
	{
		barShape.setTextureRect(IntRect(position.x, position.y, i, height));
	}
}

float ui::ProgressBar::getValue() const
{
	return value;
}

void ui::ProgressBar::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(barShape, states);
}