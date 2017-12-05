/**
uimanager.cpp
Class file for the uimanager class
CSCI 437
@author Stephen Tung
*/
#pragma once
#pragma once
#include "uimanager.h"
#include <cstdlib>

using namespace sf;

void ui::UIManager::enableStartMenu()
{
	_showStartMenu = true;
}

void ui::UIManager::disableStartMenu()
{
	_showStartMenu = false;
}

void ui::UIManager::enablePauseMenu()
{
	_showStartMenu = true;
}

void ui::UIManager::disablePauseMenu()
{
	_showStartMenu = false;
}

void ui::UIManager::enableWinScreen()
{
	_showStartMenu = true;
}

void ui::UIManager::disableWinScreen()
{
	_showStartMenu = false;
}

void ui::UIManager::enableLoseScreen()
{
	_showStartMenu = true;
}

void ui::UIManager::disableLoseScreen()
{
	_showStartMenu = false;
}

void ui::UIManager::update(float mouseX, float mouseY)
{
	if (_showStartMenu == true)
	{
		_startMenu.update(mouseX, mouseY);
	}
	else if (_showPauseMenu == true)
	{
		_pauseMenu.update(mouseX, mouseY);
	}
	else if (_showWinScreen == true)
	{
		_winScreen.update(mouseX, mouseY);
	}
	else if (_showLoseScreen == true)
	{
		_loseScreen.update(mouseX, mouseY);
	}
}

std::string ui::UIManager::select(float mouseX, float mouseY)
{
	if (_showStartMenu == true)
	{
		return _startMenu.select(mouseX, mouseY);
	}
	else if (_showPauseMenu == true)
	{
		return _pauseMenu.select(mouseX, mouseY);
	}
	else if (_showWinScreen == true)
	{
		return _winScreen.select(mouseX, mouseY);
	}
	else if (_showLoseScreen == true)
	{
		return _loseScreen.select(mouseX, mouseY);
	}
	return "None";
}

void ui::UIManager::draw(RenderTarget& target, RenderStates states) const
{
	if (_showStartMenu == true)
		target.draw(_startMenu, states);
	else if (_showPauseMenu == true)
		target.draw(_startMenu, states);
	else if (_showWinScreen == true)
		target.draw(_startMenu, states);
	else if (_showLoseScreen == true)
		target.draw(_startMenu, states);
}