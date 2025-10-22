#ifndef BOARD_OBSERVER_H
#define BOARD_OBSERVER_H

#include <memory>

class LevelManager;
class BoardObserver
{
public:
	BoardObserver(std::shared_ptr<LevelManager> levelManager);
	int GetScore();
private:
	std::shared_ptr<LevelManager> m_levelManager;
};

#endif

