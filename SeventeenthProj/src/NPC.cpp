#include "NPC.h"

NPC::NPC(const sf::Vector2f& position, const Resources::Objects& object, const std::string& name)
	: animatedObject(position, object),
	  m_name(name, Resources::instance().font(), 12), m_dialogue(object)
	  
{
	m_sp.setOrigin(sf::Vector2f(getGlobalBounds().width / 2.f, getGlobalBounds().height / 1.08f));
	m_name.setPosition(m_sp.getPosition() + sf::Vector2f(-16.f, 6.f));
	m_nameBackground.setSize(sf::Vector2f(m_name.getGlobalBounds().width * 1.09f, 14.f));
	m_nameBackground.setFillColor(sf::Color(0.f, 0.f, 0.f, 199.f));
	m_name.setFillColor(sf::Color::Yellow);
	m_nameBackground.setPosition(m_name.getPosition() + sf::Vector2f(-1.f, 0.f));
}

void NPC::update(const sf::Time delta)
{
	auto animation = m_animation.update(delta);

	if (!animation)
		m_animation.resetAnimation();
}

void NPC::draw(sf::RenderWindow& window) const
{
	window.draw(m_sp);
	window.draw(m_nameBackground);
	window.draw(m_name);
}

Resources::Objects NPC::dialogue() const
{
	return m_dialogue;
}

sf::Text NPC::name() const
{
	return m_name;
}

std::shared_ptr<sf::Sprite> NPC::sprite() const
{
	return std::make_shared<sf::Sprite>(m_sp);
}

bool NPC::wasClicked(sf::RenderWindow& window)
{
	sf::Event event;
	sf::Vector2f mousePos = window.mapPixelToCoords((sf::Mouse::getPosition(window)));

	return (m_sp.getGlobalBounds().contains(mousePos) &&
		    sf::Mouse::isButtonPressed(sf::Mouse::Left));
}