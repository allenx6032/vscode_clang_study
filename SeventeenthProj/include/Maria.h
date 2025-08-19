#pragma once

#include "NPC.h"

class Maria : public NPC
{
public:
	Maria(const sf::Vector2f& position)
		: NPC(position + sf::Vector2f(0.f, 10.f), Resources::Maria, "Maria")
	{}
};