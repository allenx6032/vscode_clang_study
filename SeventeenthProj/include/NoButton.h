#pragma once

#include "Button.h"

class NoButton : public Button
{
public:
	NoButton(const sf::Vector2f& location)
		: Button(Resources::instance().texture(Resources::NO_Button),
			Resources::instance().texture(Resources::NO_Button_Highlighted),
			Resources::instance().texture(Resources::NO_Button_Pressed),
			location)
	{}
};