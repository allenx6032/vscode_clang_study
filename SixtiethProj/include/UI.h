#ifndef UI_H
#define UI_H

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include <memory>

class BoardObserver;
class UI
{
public:
	UI(sf::Vector2f poistion, sf::Vector2f dimensions, sf::Font& font, int charSize, std::shared_ptr<BoardObserver> newObs);

	void Update();
	void Draw(sf::RenderWindow& rw);

	void SetTime(float time);

private:
	std::shared_ptr<BoardObserver> m_boardObserver;

	sf::RectangleShape m_background;

	sf::Text m_time;
	sf::Text m_score;
};

#endif