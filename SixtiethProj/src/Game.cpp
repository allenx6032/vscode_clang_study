#include "Game.h"
#include "SFML\System.hpp"

#include <iostream>

Game::Game()
{
	m_levelManager = std::shared_ptr<LevelManager>(new LevelManager(BOARD_HEIGHT, BOARD_WIDTH, 32));
	m_mainWindow.create(sf::VideoMode(BOARD_WIDTH, BOARD_HEIGHT + UI_HEIGHT, 32), "Ruby Rush! Rush those rubies!");
	m_boardObserver = std::shared_ptr<BoardObserver>(new BoardObserver(m_levelManager));

	m_font.loadFromFile("data/arial.ttf");

	sf::Vector2f UIPosition(0, 0);
	sf::Vector2f UIDimensions(UI_WIDTH, UI_HEIGHT);
	int charSize = 18;

	m_UI = std::shared_ptr<UI>(new UI(UIPosition, UIDimensions, m_font, charSize, m_boardObserver));
}

void Game::Start()
{
	m_gameState = GameState::Playing;
	GameLoop();
}

void Game::GameLoop()
{

	m_gameClock.restart();
	while (m_remainingGameTime > 0 && m_gameState != Exiting)
	{
		m_mainWindow.clear();
		Update();
		Draw();
		float elapsedTime = m_gameClock.restart().asSeconds();
		m_residualTime += elapsedTime;
		m_remainingGameTime -= elapsedTime;
		m_UI->SetTime(m_remainingGameTime);
		m_mainWindow.display();
		//std::cout << m_remainingTime << std::endl;
	}

}

void Game::Update()
{
	sf::Event event;

	int frames;
	frames = 0;

	while ((m_residualTime > m_minTimestep) && (frames < m_maxFrames))
	{
		while (m_mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
				m_levelManager->HandleClick(sf::Mouse::getPosition(m_mainWindow));
			if (event.type == sf::Event::Closed)
			{
				m_gameState = Exiting;
			}
		}
		m_levelManager->Update(0.0);
		m_UI->Update();
		m_residualTime -= m_minTimestep;
		frames++;
	}
	

}

void Game::Draw()
{
	m_levelManager->Draw(m_mainWindow);
	m_UI->Draw(m_mainWindow);
}
