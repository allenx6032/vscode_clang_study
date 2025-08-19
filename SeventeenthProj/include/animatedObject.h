#pragma once

#include "staticObject.h"

class animatedObject : public staticObject
{
public:
	using staticObject::handleCollision;

	// Constructor
	animatedObject(const sf::Vector2f& position, const Resources::Objects& object);
	virtual void update(const sf::Time delta) = 0;

protected:
	Animation m_animation;
	sf::Clock m_animationTime;
};