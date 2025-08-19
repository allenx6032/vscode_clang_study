#include "GUI.h"

GUI::GUI(const sf::Texture& texture, const sf::Vector2f& location,
	     const sf::Vector2f& size)
	: m_GUI(texture), m_closed(false)
{
	m_GUI.setPosition(location);
	m_GUI.setScale(size);
}
