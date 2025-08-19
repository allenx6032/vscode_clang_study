#pragma once

#include "staticObject.h"

class Rope : public staticObject
{
public:
	using staticObject::handleCollision;

	// Constructor
	Rope(const sf::Vector2f& position);

	// Collision Handlers
	void handleCollision(gameObject& gameObject);
	virtual void handleCollision(Player& movingObject) override;
	virtual void handleCollision(Monster& monster) override {};
};