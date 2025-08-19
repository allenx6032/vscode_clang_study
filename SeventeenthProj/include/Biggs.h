#pragma once

#include "NPC.h"

class Biggs : public NPC
{
public:
	Biggs(const sf::Vector2f& position)
		: NPC(position + sf::Vector2f(0.f, 11.f), Resources::Biggs, "Biggs")
	{}
};