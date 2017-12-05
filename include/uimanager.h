/**
uimanager.h
Header file for the uimanager class
CSCI 437
@author Stephen Tung
*/
#ifndef UIMANAGER_H
#define UIMANAGER_H
#pragma once
#include <SFML/Graphics.hpp>
#include "panel.h"
#include <memory>

using namespace sf;

namespace ui
{
	class UIManager : public Drawable
	{
	public:
		void enableStartMenu();
		void disableStartMenu();
		void enablePauseMenu();
		void disablePauseMenu();
		void enableWinScreen();
		void disableWinScreen();
		void enableLoseScreen();
		void disableLoseScreen();

		void update(float mouseX, float mouseY);
		std::string select(float mouseX, float mouseY);

	private:
		Panel _startMenu;
		bool _showStartMenu;
		Panel _pauseMenu;
		bool _showPauseMenu;
		Panel _winScreen;
		bool _showWinScreen;
		Panel _loseScreen;
		bool _showLoseScreen;

		std::vector <std::shared_ptr<Panel>> _menus;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}
#endif
