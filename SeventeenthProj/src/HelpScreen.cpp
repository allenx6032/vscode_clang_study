#pragma once
#include "HelpScreen.h"


HelpScreen::HelpScreen(unsigned int WindowWidth, unsigned int WindowHeight)
	: m_window(sf::VideoMode(WindowWidth, WindowHeight), "Mushroom Game", sf::Style::Fullscreen),
	  m_menuSprite(Resources::instance().texture(Resources::MenuBackground))
{
	m_menuSprite.setScale(0.72f, 0.72f);
	initTitle();
	initInstructions();
	initButton();
}


void HelpScreen::run()
{
	while (m_window.isOpen())
	{
		draw();
		updateEvents();
	}
}


void HelpScreen::draw()
{
	m_window.clear(sf::Color::White);

	// Draw the screen
	m_window.draw(m_menuSprite);
	m_window.draw(title);
	m_window.draw(row1);
	m_window.draw(row2);
	m_window.draw(row3);
	m_window.draw(back);

	m_window.display();
}


void HelpScreen::updateEvents()
{
	sf::Vector2f mousePos;
	mousePos.x = (float)(sf::Mouse::getPosition(m_window).x);
	mousePos.y = (float)(sf::Mouse::getPosition(m_window).y);
	for (auto event = sf::Event(); m_window.pollEvent(event); )
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		}

		if (back.getGlobalBounds().contains(mousePos))
		{
			back.setCharacterSize(77);
			back.setPosition(710 - 10, 480 - 10);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				m_window.close();
		}
		else
		{
			back.setCharacterSize(67);
			back.setPosition(710, 480);
		}
	}
}


void HelpScreen::initTitle()
{
	titleFont.loadFromFile("resources/Blueberry.ttf");
	title.setString("Instructions");
	title.setFont(titleFont);
	title.setCharacterSize(130);
	title.setFillColor(sf::Color::Black);
	title.setPosition(80, 30);
}


void HelpScreen::initButton()
{
	buttonsFont.loadFromFile("resources/Blueberry.ttf");

	back.setString("BACK");
	back.setFont(buttonsFont);
	back.setFillColor(sf::Color::Black);
	back.setCharacterSize(67);
	back.setPosition(710, 480);
}

void HelpScreen::initInstructions()
{
	instructionsFont.loadFromFile("resources/helpFont.ttf");

	row1.setString("MOVEMENT: Keyboard arrows, CTRL for fighting and ALT for jumping.");
	row1.setFont(instructionsFont);
	row1.setFillColor(sf::Color::Black);
	row1.setPosition(90, 250);
	row1.setCharacterSize(47);
	row1.setOutlineColor(sf::Color::Black);
	row1.setOutlineThickness(0.8);

	row2.setString("In addition, an upper arrow to move through the portal.");
	row2.setFont(instructionsFont);
	row2.setFillColor(sf::Color::Black);
	row2.setPosition(90.f, 320.f);
	row2.setCharacterSize(47);
	row2.setOutlineColor(sf::Color::Black);
	row2.setOutlineThickness(0.8);

	row3.setString("GOAL: Kill all the mushrooms and go through the portals.");
	row3.setFont(instructionsFont);
	row3.setFillColor(sf::Color::Black);
	row3.setPosition(90.f, 390.f);
	row3.setCharacterSize(47);
	row3.setOutlineColor(sf::Color::Black);
	row3.setOutlineThickness(0.8);
}
