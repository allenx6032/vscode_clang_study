#pragma once

#include "Button.h"

class NextButton : public Button
{
public:
	NextButton(const sf::Vector2f& location)
		: Button(Resources::instance().texture(Resources::NEXT_Button),
			     Resources::instance().texture(Resources::NEXT_Button_Highlighted),
			     Resources::instance().texture(Resources::NEXT_Button_Pressed),
			     location)
	{}
};