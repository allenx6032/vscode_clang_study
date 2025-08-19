#include "DialogueGUI.h"
#include "Info.h"

DialogueGUI::DialogueGUI(const Resources::Objects& npc, const sf::Text& name, std::shared_ptr<sf::Sprite> sprite)
	: GUI(Resources::instance().texture(Resources::Dialogue), sf::Vector2f(415.f, 240.f),
		sf::Vector2f(1.f, 1.f)),
	OK_Button(sf::Vector2f(m_GUI.getPosition() + sf::Vector2f(475.f, 199.f))),
	NEXT_Button(sf::Vector2f(m_GUI.getPosition() + sf::Vector2f(448.f, 150.f))),
	BACK_Button(sf::Vector2f(m_GUI.getPosition() + sf::Vector2f(393.f, 150.f))),
	END_Button(sf::Vector2f(m_GUI.getPosition() + sf::Vector2f(8.f, 200.f))),
	YES_Button(sf::Vector2f(m_GUI.getPosition() + sf::Vector2f(475.f, 199.f))),
	NO_Button(sf::Vector2f(m_GUI.getPosition() + sf::Vector2f(420.f, 199.f))),
	page(0),
	m_dialogue(Resources::instance().dialogues(npc)),
	m_name(name),
	m_npc(sprite)
{
	for (auto& dialogue : m_dialogue)
	{
		dialogue->setPosition(m_GUI.getPosition() + sf::Vector2f(170.f, 50.f));
		dialogue->setFillColor(sf::Color::Black);
	}
	m_npc->setPosition(m_GUI.getPosition() + sf::Vector2f(75.f, 120.f));
	m_name.setPosition(m_GUI.getPosition() + sf::Vector2f(60.f, 125.f));
	m_name.setCharacterSize(13);
	m_name.setFillColor(sf::Color::White);
}

void DialogueGUI::draw(sf::RenderWindow& window)
{
	window.draw(m_GUI);
	window.draw(*m_npc);
	window.draw(m_name);

	// pages have different buttons
	if (page == m_dialogue.size() - 2 && m_name.getString() == "Shanks")
	{
		YES_Button.draw(window);
		NO_Button.draw(window);
	}
	else if (page == m_dialogue.size() - 1)
	{
		OK_Button.draw(window);
		END_Button.draw(window);
	}
	else if (page == 0)
	{
		NEXT_Button.draw(window);
		END_Button.draw(window);
	}
	else
	{
		NEXT_Button.draw(window);
		BACK_Button.draw(window);
		END_Button.draw(window);
	}
	// pages have different text
	if (m_dialogue[page])
		window.draw(*m_dialogue[page]);
}

void DialogueGUI::handleEvents(sf::RenderWindow& window)
{
	// detect click
	if (OK_Button.wasClicked(window) && page == m_dialogue.size() - 1 ||
		END_Button.wasClicked(window) ||
		NO_Button.wasClicked(window))
		m_closed = true;

	else if (NEXT_Button.wasClicked(window) && page < m_dialogue.size() - 1)
		page++;

	else if (BACK_Button.wasClicked(window) && page > 0)
		page--;

	else if (YES_Button.wasClicked(window) && page == m_dialogue.size() - 2)
	{
		if (Map::instance().player()->getData().level >= 10)
		{
			Info::instance().addGUI(Info::Arrival);
			m_closed = true;
		}
		else
			page++;
	}
}
