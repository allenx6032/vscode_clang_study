#include "UI.h"
#include "BoardObserver.h"


UI::UI(sf::Vector2f position, sf::Vector2f dimensions, sf::Font& font, int charSize, std::shared_ptr<BoardObserver> newObs)
{
	m_boardObserver = newObs;

	m_background.setPosition(position);
	m_background.setSize(dimensions);
	m_background.setFillColor(sf::Color::Black);

	m_time.setFont(font);
	m_time.setCharacterSize(charSize);
	m_time.setColor(sf::Color::White);
	m_time.setString("0");

	m_score.setFont(font);
	m_score.setCharacterSize(charSize);
	m_score.setColor(sf::Color::White);
	m_score.setString("0");

	m_score.setPosition(position);
	m_time.setPosition(sf::Vector2f(position.x + dimensions.x / 2 , position.y));
}

void UI::Update()
{
	m_score.setString("Score: " + std::to_string(m_boardObserver->GetScore()));
}

void UI::Draw(sf::RenderWindow& rw)
{
	rw.draw(m_background);
	rw.draw(m_score);
	rw.draw(m_time);
}

void UI::SetTime(float time)
{
	m_time.setString("Time: " + std::to_string((int)std::floor(time)));
}