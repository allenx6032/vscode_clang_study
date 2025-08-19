#pragma once

#include "NPC.h"

class Lucas : public NPC
{
public:
	Lucas(const sf::Vector2f& position)
		: NPC(position, Resources::Lucas, "Lucas")
	{}
};