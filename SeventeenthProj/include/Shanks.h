#pragma once

#include "NPC.h"

class Shanks : public NPC
{
public:
	Shanks(const sf::Vector2f& position)
		: NPC(position + sf::Vector2f(0.f, 7.f), Resources::Shanks, "Shanks")
	{}
};