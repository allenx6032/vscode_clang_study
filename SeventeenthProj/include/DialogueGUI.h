#pragma once

#include <memory>
#include "GUI.h"
#include "OkButton.h"
#include "NextButton.h"
#include "BackButton.h"
#include "EndButton.h"
#include "YesButton.h"
#include "NoButton.h"
#include "Animation.h"

class DialogueGUI : public GUI
{
public:
	DialogueGUI(const Resources::Objects& npc, const sf::Text& name, std::shared_ptr<sf::Sprite> sprite);

	virtual void draw(sf::RenderWindow& window) override;
	virtual void handleEvents(sf::RenderWindow& window) override;

private:
	std::vector<std::shared_ptr<sf::Text>> m_dialogue;
	std::shared_ptr<sf::Sprite> m_npc;
	sf::Text m_name;
	int page;	// current page being drawn
	OkButton OK_Button;
	NextButton NEXT_Button;
	BackButton BACK_Button;
	EndButton END_Button;
	YesButton YES_Button;
	NoButton NO_Button;
};	