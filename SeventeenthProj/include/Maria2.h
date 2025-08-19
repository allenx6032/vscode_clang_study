#pragma once

#include "NPC.h"

class Maria2 : public NPC
{
public:
	Maria2(const sf::Vector2f& position)
		: NPC(position, Resources::Maria2, "Maria")
	{}
};