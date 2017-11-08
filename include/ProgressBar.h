/**
ProgressBar.h
Header file for the ProgressBar class
CSCI 437
@author Stephen Tung
*/
#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace ui
{
	class ProgressBar : public Drawable, public Transformable
	{
	public:
		ProgressBar();
		ProgressBar(Vector2f pos, float width, float val);
		void setValue(float val);
		float getValue() const;
		
	private:
		void draw(RenderTarget& target, RenderStates states) const;
		Vector2f position;
		float height;
		float value;
		Text text;
		RectangleShape barShape;
		Texture texture;
		const Texture* barTexture;
	};
}

#endif PROGRESSBAR_H