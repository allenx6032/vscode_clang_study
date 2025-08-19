#include "Damage.h"
#include "Resources.h"

Damage::Damage(std::string type, const int& amount, const sf::Vector2f& location)
	: m_delete(false)
{
	if (type == "Player")
		m_damage.setFillColor(sf::Color( 242.f, 140.f, 40.f));
	else
		m_damage.setFillColor(sf::Color( 208.f, 51.f, 255.f ));

	m_damage.setFont(Resources::instance().font());
	m_damage.setStyle(sf::Text::Bold);
	m_damage.setCharacterSize(48.f);
	m_damage.setOutlineColor(sf::Color(0.f, 0.f, 0.f ));
	m_damage.setOutlineThickness(3.f);
	m_damage.setPosition(location - sf::Vector2f(0.f, 40.f));
	m_damage.setString(std::to_string(amount));
}

void Damage::update()
{
	fadeOut();
	m_damage.move(0.f, -1.f);
}

void Damage::draw(sf::RenderWindow& window)
{
	window.draw(m_damage);
}

void Damage::fadeOut()
{
	// disappear little by little
	m_damage.setFillColor(m_damage.getFillColor() - sf::Color(0.f, 0.f, 0.f, 4.f));
	m_damage.setOutlineColor(m_damage.getOutlineColor() - sf::Color(0.f, 0.f, 0.f, 4.f));

	if (m_damage.getFillColor().a <= 0.f)
		m_delete = true;
}

bool Damage::deletion()
{
	return m_delete;
}
