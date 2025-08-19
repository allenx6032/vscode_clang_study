#pragma once

#include "NPC.h"

class Pio : public NPC
{
public:
	Pio(const sf::Vector2f& position)
		: NPC(position, Resources::Pio, "Pio")
	{}
};