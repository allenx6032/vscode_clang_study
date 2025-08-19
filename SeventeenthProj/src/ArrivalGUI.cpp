#include "ArrivalGUI.h"
#include "Resources.h"
#include "Controller.h"

constexpr auto PictureTime = 10.f;

ArrivalGUI::ArrivalGUI()
	: GUI(Resources::instance().texture(Resources::Arrival_Texture), sf::Vector2f(0.f, 0.f),
		sf::Vector2f(1.f, 1.f)), m_sound(Resources::instance().sound(Resources::Arrival))
{
	Map::instance().music()->stop();
	m_sound.play();
}

void ArrivalGUI::draw(sf::RenderWindow& window)
{
	window.draw(m_GUI);
	
	if (m_clock.getElapsedTime().asSeconds() > PictureTime)
		m_closed = true;
}

void ArrivalGUI::handleEvents(sf::RenderWindow& window)
{
}

ArrivalGUI::~ArrivalGUI()
{
	Controller::finishGame();
}
