#include "Wall.h"

Wall::Wall(const sf::Vector2f& position)
	: staticObject(position, Resources::instance().texture(Resources::Wall))
{
	m_sp.setScale(0.13f, 0.13f);
	m_sp.setOrigin(m_sp.getTextureRect().width / 2.5f, m_sp.getTextureRect().height - 100);
}

void Wall::handleCollision(gameObject& gameObject)
{
	// ignore self collision
	if (&gameObject == this) return;

	// use double dispatch to find which object
	gameObject.handleCollision(*this);
}

void Wall::handleCollision(Player& player)
{
	player.handleCollision(*this);
}

void Wall::handleCollision(Monster& monster)
{
	monster.handleCollision(*this);
}
