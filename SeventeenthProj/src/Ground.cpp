#include "Ground.h"

Ground::Ground(const sf::Vector2f& position)
	: staticObject(position, Resources::instance().texture(Resources::Ground))
{
	m_sp.setScale(0.13f, 0.13f);
	m_sp.setOrigin(m_sp.getTextureRect().width / 2.5f, m_sp.getTextureRect().height - 150);
}

void Ground::handleCollision(gameObject& gameObject)
{
	// ignore self collision
	if (&gameObject == this) return;

	// use double dispatch to find which object
	gameObject.handleCollision(*this);
}

void Ground::handleCollision(Player& player)
{
	player.handleCollision(*this);
}

void Ground::handleCollision(Monster& monster)
{
	monster.handleCollision(*this);
}
