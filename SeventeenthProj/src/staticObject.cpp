#include "staticObject.h"

staticObject::staticObject(const sf::Vector2f& position)
	: gameObject(position)
{
}

staticObject::staticObject(const sf::Vector2f& position, const sf::Texture& texture)
	: gameObject(position, texture)
{
}