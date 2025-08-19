#pragma once

#include "Ladder.h"

Ladder::Ladder(const sf::Vector2f& position)
	: staticObject(position, Resources::instance().texture(Resources::Ladder))
{
	m_sp.setScale(0.13f, 0.13f);
	m_sp.setOrigin(m_sp.getTextureRect().width / 2.5f, m_sp.getTextureRect().height - 100);
}

void Ladder::handleCollision(gameObject& gameObject)
{
	// ignore self collision
	if (&gameObject == this) return;

	// use double dispatch to find which object
	gameObject.handleCollision(*this);
}

void Ladder::handleCollision(Player& player)
{
	player.handleCollision(*this);
}