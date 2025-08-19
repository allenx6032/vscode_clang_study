#pragma once

#include "Button.h"

class BackButton : public Button
{
public:
	BackButton(const sf::Vector2f& location)
		: Button(Resources::instance().texture(Resources::BACK_Button),
			     Resources::instance().texture(Resources::BACK_Button_Highlighted),
			     Resources::instance().texture(Resources::BACK_Button_Pressed),
			     location)
	{}
};