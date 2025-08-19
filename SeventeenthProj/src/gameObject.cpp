#pragma once

#include "gameObject.h"

gameObject::gameObject(const sf::Vector2f& position)
	: m_isDeleted(false)
{
	m_sp.setPosition(position);
	m_effect.setPosition(10000.f, 10000.f);
}

// Constructor
gameObject::gameObject(const sf::Vector2f& position, const sf::Texture& texture)
	: m_isDeleted(false)
{
	m_sp.setTexture(texture);
	m_sp.setPosition(position);	
}

void gameObject::setImage(const sf::Texture& texture)
{
	m_sp.setTexture(texture);
}

void gameObject::setPosition(sf::Vector2f position)
{
	m_sp.setPosition(position);
}

void gameObject::draw(sf::RenderWindow& window) const
{
	window.draw(m_effect);
	window.draw(m_sp);
}

sf::Vector2f gameObject::getPosition() const
{
	return m_sp.getPosition();
}

bool gameObject::collidesWith(const sf::FloatRect& other) const
{
	return m_sp.getGlobalBounds().intersects(other);
}

sf::FloatRect gameObject::getGlobalBounds() const
{
	return m_sp.getGlobalBounds();
}

bool gameObject::isDeleted() const
{
	return m_isDeleted;
}

void gameObject::remove()
{
	m_isDeleted = true;
}

void gameObject::handleCollision(gameObject& gameObject)
{
	// ignore self collision
	if (&gameObject == this) return;

	// use double dispatch to find which object
	gameObject.handleCollision(*this);
}
