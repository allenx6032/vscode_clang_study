#pragma once

#include "Button.h"

class YesButton : public Button
{
public:
	YesButton(const sf::Vector2f& location)
		: Button(Resources::instance().texture(Resources::YES_Button),
			     Resources::instance().texture(Resources::YES_Button_Highlighted),
			     Resources::instance().texture(Resources::YES_Button_Pressed),
			     location)
	{}
};