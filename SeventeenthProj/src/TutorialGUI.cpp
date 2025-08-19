#include "TutorialGUI.h"
#include "Resources.h"

TutorialGUI::TutorialGUI()
	: GUI(Resources::instance().texture(Resources::Tutorial), sf::Vector2f(375.f, 250.f),
		sf::Vector2f(1.f, 1.f)),
	OK_Button(sf::Vector2f(m_GUI.getPosition() + sf::Vector2f(556.f, 283.f)))
{
}

void TutorialGUI::draw(sf::RenderWindow& window)
{
	window.draw(m_GUI);
	OK_Button.draw(window);
}

void TutorialGUI::handleEvents(sf::RenderWindow& window)
{
	// detect click
	if (OK_Button.wasClicked(window))
		m_closed = true;
}
