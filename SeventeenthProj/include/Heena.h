#pragma once

#include "NPC.h"

class Heena : public NPC
{
public:
	Heena(const sf::Vector2f& position)
		: NPC(position, Resources::Heena, "Heena")
	{}
};