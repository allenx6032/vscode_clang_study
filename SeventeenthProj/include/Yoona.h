#pragma once

#include "NPC.h"

class Yoona : public NPC
{
public:
	Yoona(const sf::Vector2f& position)
		: NPC(position + sf::Vector2f(0.f, 17.f), Resources::Yoona, "Yoona")
	{}
};