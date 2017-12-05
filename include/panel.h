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
#include "button.h"
#include <memory>

using namespace sf;

namespace ui
{
	class Panel : public Drawable, public Transformable
	{
	public:
		Panel(const Vector2f& size, const std::string& title, const Font& pFont);
		//Panel(const Panel&) = delete;
		Panel& operator=(const Panel&) = delete;

		void update(float mouseX, float mouseY);
		std::string select(float mouseX, float mouseY);

		std::shared_ptr<Button> addButton(const Button& btn, const Vector2f& pos);

	private:
		RectangleShape _shape;
		const Color PANEL_COLOR = Color(100, 100, 100, 180);
		const Color TEXT_COLOR = Color::White;
		Font _font;
		Text _title;

		std::vector<std::shared_ptr<Button>> _btns;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}
#endif
