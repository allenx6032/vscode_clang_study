#ifndef GAME_H
#define GAME_H

#include "LevelManager.h"
#include "UI.h"
#include "BoardObserver.h"

class Game
{
public:
	Game();

	//Start game
	void Start();

private:
	//Enum to identify state of the game
	enum GameState
	{
		Playing,
		Exiting,
	};

	//Holds current game state
	GameState m_gameState;

	//Main game loop
	void GameLoop();

	//Draw board
	void Draw();

	//Update board
	void Update();

	//Board dimensions
	const int BOARD_HEIGHT = 480;
	const int BOARD_WIDTH = 320;

	//UI Dimensions
	const int UI_WIDTH = BOARD_WIDTH;
	const int UI_HEIGHT = 32;

	//Game window
	sf::RenderWindow m_mainWindow;

	//Fixed framerate
	const float m_minTimestep = sf::seconds(1.f / 60.f).asSeconds();
	const int m_maxFrames = 5;
	float m_residualTime = 0;

	//Game time limit in seconds
	const float m_maxTime = 60;
	//Remaining time
	float m_remainingGameTime = m_maxTime;
	//Game clock
	sf::Clock m_gameClock;

	//Font for UI
	sf::Font m_font;

	//Pointer to level manager
	std::shared_ptr<LevelManager> m_levelManager;
	//Pointer to ui
	std::shared_ptr<UI> m_UI;
	//Pointer to board observer
	std::shared_ptr<BoardObserver> m_boardObserver;
};

#endif

