#pragma once

#include "NPC.h"

class Bari : public NPC
{
public:
	Bari(const sf::Vector2f& position)
		: NPC(position + sf::Vector2f(0.f, 11.f), Resources::Bari, "Bari")
	{}
};