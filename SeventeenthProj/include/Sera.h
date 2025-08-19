#pragma once

#include "NPC.h"

class Sera : public NPC
{
public:
	Sera(const sf::Vector2f& position)
		: NPC(position, Resources::Sera, "Sera")
	{}
};