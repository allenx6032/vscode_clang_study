#pragma once

#include <SFML/SFML_graphics.hpp>

class Damage
{
public:
	Damage(std::string type, const int& amount, const sf::Vector2f& location);
	void update();
	void draw(sf::RenderWindow& window);
	void fadeOut();
	bool deletion();

private:
	sf::Text m_damage;
	sf::Font m_damageFont;
	bool m_delete;
};