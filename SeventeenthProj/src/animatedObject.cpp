#include "animatedObject.h"

animatedObject::animatedObject(const sf::Vector2f& position, const Resources::Objects& object)
	: staticObject(position),
	  m_animation(Resources::instance().animationData(object), Direction::Stay, m_sp)
{
}
