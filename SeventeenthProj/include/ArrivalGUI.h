#pragma once

#include "GUI.h"

class ArrivalGUI : public GUI
{
public:
	ArrivalGUI();

	virtual void draw(sf::RenderWindow& window) override;
	virtual void handleEvents(sf::RenderWindow& window) override;

	~ArrivalGUI();
private:
	sf::Sound m_sound;
	sf::Clock m_clock;
};