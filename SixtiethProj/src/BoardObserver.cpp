#include "BoardObserver.h"
#include "LevelManager.h"


BoardObserver::BoardObserver(std::shared_ptr<LevelManager> levelManager)
{
	m_levelManager = levelManager;
}
int BoardObserver::GetScore()
{
	return m_levelManager->GetScore();
}
