#pragma once

#include "gameObject.h"
#include "Direction.h"
#include "Animation.h"
#include "PhysicsData.h"
#include "Resources.h"
#include "Data.h"

class movingObject : public gameObject
{
public:
	// Constructors
	movingObject(const sf::Vector2f& position, const Resources::Objects& object,
		         const int& deathSound);
	
	// Functions
	virtual void update(const sf::Time delta) = 0;
	void wasHit(const int& damage, const sf::Vector2f& direction);
	void knockback(const sf::Vector2f& direction);					// knock back when hit
	void updatePhysics();
	int randomDamage() const;
	bool isDead();													// checks if HP is negative
	void respawn(bool enable = false);								// revives object and sends back to spawn
	Data getData() const;									// read data of object

	// Variables
protected:
	sf::Vector2f m_spawnLocation;
	Direction m_dir = Direction::Stay;
	Data data;
	PhysicsData physics;
	Animation m_animation;
	sf::Clock m_hitTime;		// how long hit effect lasts
	sf::Sound m_deathSound;
	bool m_jump;
};