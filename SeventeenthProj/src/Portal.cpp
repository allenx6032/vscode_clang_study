#include "Portal.h"

Portal::Portal(const sf::Vector2f& position)
	: animatedObject(position, Resources::Portal),
	   m_destination(-1), m_exitPortal(-1)
{
	m_sp.setOrigin(sf::Vector2f(getGlobalBounds().width / 2.f, getGlobalBounds().height / 1.08f));
}

Portal::Portal(const sf::Vector2f& position, const int& destination)
	: animatedObject(position, Resources::Portal),
	  m_destination(destination), m_exitPortal(-1)
{
	m_sp.setOrigin(sf::Vector2f(getGlobalBounds().width / 2.f, getGlobalBounds().height / 1.08f));
}

Portal::Portal(const sf::Vector2f& position, const int& destination, const int& exitPortal)
	: animatedObject(position, Resources::Portal),
	  m_destination(destination), m_exitPortal(exitPortal)
{
	m_sp.setOrigin(sf::Vector2f(getGlobalBounds().width / 2.f, getGlobalBounds().height / 1.08f));
}

void Portal::update(const sf::Time delta)
{
	auto animation = m_animation.update(delta);
	
	if (!animation)
		m_animation.resetAnimation();
}

int Portal::destination()
{
	return m_destination;
}

int Portal::exitPortal()
{
	return m_exitPortal;
}