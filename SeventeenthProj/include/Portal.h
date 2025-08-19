#pragma once

#include "animatedObject.h"

class Portal : public animatedObject
{
public:
	using staticObject::handleCollision;

	// Constructor
	Portal(const sf::Vector2f& position);
	Portal(const sf::Vector2f& position, const int& destination);
	Portal(const sf::Vector2f& position, const int& destination, const int& exitPortal);

	// Functions
	virtual void update(const sf::Time delta);
	int destination();
	int exitPortal();

	// Collision Handlers
	void handleCollision(gameObject& gameObject) {};
	virtual void handleCollision(Player& movingObject) {};
	virtual void handleCollision(Monster& monster) {};

private:
	int m_destination;	// mapID of destination
	int m_exitPortal;	// which portal to exit from?
};