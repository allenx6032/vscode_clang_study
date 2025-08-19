#pragma once
#include <SFML/SFML_Graphics.hpp>
#include "Menu.h"

class HelpScreen
{
public:
	// Constractor
	HelpScreen(unsigned int WindowWidth, unsigned int WindowHeight);

	// Public Functions
	void run();

private:
	// Members
	sf::RenderWindow m_window;

	float m_windowHeight;
	float m_windowWidth;

	sf::Sprite m_menuSprite;

	sf::Font titleFont;
	sf::Font buttonsFont;
	sf::Font instructionsFont;
	sf::Text title;
	sf::Text back;

	sf::Text row1;
	sf::Text row2;
	sf::Text row3;
	sf::Text row4;
	sf::Text row5;

	// Private Functions
	void draw();
	void updateEvents();
	void initTitle();
	void initButton();
	void initInstructions();

};