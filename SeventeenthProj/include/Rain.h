#pragma once

#include "NPC.h"

class Rain : public NPC
{
public:
	Rain(const sf::Vector2f& position)
		: NPC(position, Resources::Rain, "Rain")
	{}
};