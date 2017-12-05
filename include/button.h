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
#include <string>

using namespace sf;
namespace ui
{
	namespace state
	{
		enum
		{
			unselected = 0,
			hover = 1,
			selected = 2
		};
	};
	class Button : public Drawable, public Transformable
	{
	public:
		Button(const std::string& label, const Font& bFont, const Vector2f& size);
		Button(const Button& btn);
		Button& operator=(const Button& btn);
		
		void unselected();
		void hover();
		void selected();

		void setPosition(Vector2f pos);
		bool mouseInButton(float mouseX, float mouseY);
		void update(float mouseX, float mouseY);
		std::string select(float mouseX, float mouseY);

	private:
		Uint32 _state;
		const Color UNSELECTED_COLOR = Color(125, 230, 240);
		const Color HOVER_COLOR = Color(150, 240, 245);
		const Color SELECTED_COLOR = Color(200, 250, 255);
		const Color TEXT_COLOR = Color::Black;
		RectangleShape _shape;
		Text _text;
		bool _mouseInButton;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}
#endif
