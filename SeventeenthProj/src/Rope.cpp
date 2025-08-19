#pragma once

#include "Rope.h"

Rope::Rope(const sf::Vector2f& position)
	: staticObject(position, Resources::instance().texture(Resources::Rope))
{
	m_sp.setScale(0.13f, 0.13f);
	m_sp.setOrigin(m_sp.getTextureRect().width / 2.5f, m_sp.getTextureRect().height - 100);
}

void Rope::handleCollision(gameObject& gameObject)
{
	// ignore self collision
	if (&gameObject == this) return;

	// use double dispatch to find which object
	gameObject.handleCollision(*this);
}

void Rope::handleCollision(Player& player)
{
	player.handleCollision(*this);
}