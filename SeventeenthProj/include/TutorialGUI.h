#pragma once

#include "GUI.h"
#include "OkButton.h"

class TutorialGUI : public GUI
{
public:
	TutorialGUI();

	virtual void draw(sf::RenderWindow& window) override;
	virtual void handleEvents(sf::RenderWindow& window) override;

private:
	OkButton OK_Button;
};