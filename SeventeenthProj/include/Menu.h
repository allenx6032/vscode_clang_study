#pragma once
#include "Controller.h"
#include "HelpScreen.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>

class Menu
{
public:
	//----------------------
	enum Settings
	{
		WindowWidth = 1366,
		WindowHeight = 768,
	};
	//----------------------

	// Constructor
	Menu();							// Constractor

	// Public functions
	void run();

private:
	// Members
	sf::RenderWindow m_window;
	int m_windowHeight;
	int m_windowWidth;
	sf::Sprite m_menuSprite;
	sf::Sound m_sound;

	// Textes & Fonts
	sf::Font titleFont;
	sf::Font buttonsFont;
	sf::Text title1;
	sf::Text title2;
	sf::Text start;
	sf::Text help;
	sf::Text exit;

	// Private functions
	void draw();					// Draws the objects on the screen.
	void updateEvents();			// Handles screen events.
	void initTitle();
	void initButtons();


};
