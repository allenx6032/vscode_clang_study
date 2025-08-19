#pragma once
#include "movingObject.h"

constexpr auto HitDuration = 0.5f;

movingObject::movingObject(const sf::Vector2f& position, const Resources::Objects& object,
	                       const int& deathSound)
	: gameObject(position),
	  m_deathSound(Resources::instance().sound(deathSound)),
	  m_animation(Resources::instance().animationData(object), Direction::Stay, m_sp),
	  m_spawnLocation(position), m_jump(false)
{
}

void movingObject::wasHit(const int& damage, const sf::Vector2f& direction)
{
	if (damage > 1 &&
		m_hitTime.getElapsedTime().asSeconds() >= HitDuration &&
		m_dir != Direction::Attack1 && m_dir != Direction::Attack2 &&
		m_dir != Direction::ProneStab && !data.dead)
	{
		m_hitTime.restart();
		m_dir = Direction::Hit;
		data.wasHit = true;
		data.HP -= damage;			// reduce health points
		if (data.HP <= 0)
			data.HP = 0;			// hp can't go under 0
		else
			knockback(direction);	// no knockback when dead
	}
}

void movingObject::knockback(const sf::Vector2f& direction)
{
	if (m_jump)
		return;

	// knocks back object after being hit
	if (direction == sf::Vector2f(1.f, 1.f)) // attacker is facing right
	{
		physics.velocity = sf::Vector2f(physics.knockback.x, physics.velocity.y - physics.knockback.y);
	}
	else
	{
		physics.velocity = sf::Vector2f(-physics.knockback.x, physics.velocity.y - physics.knockback.y);
	}
}

void movingObject::updatePhysics()
{
	// gravity
	physics.velocity.y += physics.gravity;
	
	if (std::abs(physics.velocity.x) > physics.velocityMaxY)
	{
		physics.velocity.y = physics.velocityMaxY * ((physics.velocity.y < 0.f) ? -1.f : 1.f);
	}
	if (std::abs(physics.velocity.y) > physics.velocityMaxY)
	{
		physics.velocity.y = physics.velocityMaxY;
	}

	// deceleration
	physics.velocity *= physics.drag;

	// limit deceleration
	if (std::abs(physics.velocity.x) < physics.velocityMin)
	{
		physics.velocity.x = 0.f;
	}
	if (std::abs(physics.velocity.x) > physics.velocityMax)
	{
		physics.velocity.x = 0.f;
	}
	if (std::abs(physics.velocity.y) < physics.velocityMin)
	{
		physics.velocity.y = 0.f;
	}

	m_sp.move(physics.velocity);
}

void movingObject::respawn(bool enable)
{
	// once enabled, respawns on next func call so we can add effects in-between calls
	if (data.respawn)
	{
		data.HP = data.MaxHP;
		data.dead = false;
		data.wasHit = false;
		physics.drag = 1.09f;
		setPosition(m_spawnLocation - sf::Vector2f(0.f, 20.f));
		m_dir = Direction::Stay;
		m_animation.direction(m_dir);
		m_effect.setPosition(10000.f, 10000.f);
		m_animation.resetAnimation();
		data.respawn = false;
	}
	data.respawn = enable;
}

int movingObject::randomDamage() const
{
	int maxDamage = data.damage * 1.2f;
	int minDamage = data.damage * 0.8f;

	return (rand() % maxDamage) + minDamage;
}

bool movingObject::isDead()
{
	if (data.HP == 0 && data.dead && m_dir != Direction::Dead)
		return true;

	if (data.HP == 0 && !data.dead ||
		data.HP == data.MaxHP && data.dead)
	{
		m_dir = Direction::Dead;
		m_animation.direction(m_dir);
		m_animation.resetAnimation();
		return true;
	}
	return false;
}

Data movingObject::getData() const
{
	return data;
}
