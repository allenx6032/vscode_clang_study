#pragma once

#include "Button.h"

class EndButton : public Button
{
public:
	EndButton(const sf::Vector2f& location)
		: Button(Resources::instance().texture(Resources::END_Button),
			     Resources::instance().texture(Resources::END_Button_Highlighted),
			     Resources::instance().texture(Resources::END_Button_Pressed),
			     location)
	{}
};