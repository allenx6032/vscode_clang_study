#pragma once

#include "NPC.h"

class Peter : public NPC
{
public:
	Peter(const sf::Vector2f& position)
		: NPC(position, Resources::Peter, "Peter")
	{}
};