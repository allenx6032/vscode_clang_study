#include "Button.h"

Button::Button(const sf::Texture& normal, const sf::Texture& highlighted,
	           const sf::Texture& pressed, const sf::Vector2f& location)
	: m_normal(normal),
	  m_highlighted(highlighted),
	  m_pressed(pressed),
	  m_button(normal)
{
	m_button.setPosition(location);
}

void Button::draw(sf::RenderWindow& window) const
{
	window.draw(m_button);
}

bool Button::wasClicked(sf::RenderWindow& window)
{
	sf::Event event;
	sf::Vector2f mousePos = window.mapPixelToCoords((sf::Mouse::getPosition(window)));

	if (m_button.getGlobalBounds().contains(mousePos))
	{
		m_button.setTexture(m_highlighted);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			m_clickDelay.getElapsedTime().asSeconds() > 0.6f)
		{
			m_clickDelay.restart();
			m_button.setTexture(m_pressed);
			return true;
		}
	}
	else
			m_button.setTexture(m_normal);
	return false;
}