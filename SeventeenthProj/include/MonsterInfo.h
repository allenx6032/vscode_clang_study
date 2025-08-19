#pragma once

#include <SFML/SFML_graphics.hpp>
#include "Data.h"

class MonsterInfo
{
public:
	MonsterInfo(const Data& data);
	void update(const Data& data, const sf::Vector2f& location, const sf::FloatRect& boundingRectangle);
	void draw(sf::RenderWindow& window);
	void setName(const std::string& newName);
	void setLevel(const int& newLevel);

private:
	void init(sf::Text& text, const int& size);
	void init(sf::RectangleShape& bar, const sf::Color& color, const sf::Vector2f& size);

	sf::Text name;
	sf::RectangleShape nameBackground;

	sf::Text level;
	sf::RectangleShape levelBackground;

	sf::RectangleShape HPbar;
	sf::RectangleShape HPbackground1;
	sf::RectangleShape HPbackground2;
	
	sf::Font infoFont;
	bool m_delete;
};