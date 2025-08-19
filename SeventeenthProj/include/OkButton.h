#pragma once

#include "Button.h"

class OkButton : public Button
{
public:
	OkButton(const sf::Vector2f& location)
		: Button(Resources::instance().texture(Resources::OK_Button),
			     Resources::instance().texture(Resources::OK_Button_Highlighted),
			     Resources::instance().texture(Resources::OK_Button_Pressed),
			     location)
	{}
};