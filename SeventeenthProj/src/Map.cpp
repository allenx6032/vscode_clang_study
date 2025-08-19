#include "Map.h"

Map::Map()
	: m_mapWidth(0), m_mapHeight(0), 
	  m_background(std::make_unique<sf::Sprite>()),
	  m_map(std::make_unique<sf::Sprite>()),
	  m_music(std::make_unique<sf::Sound>(Resources::instance().music(Map::MushroomTown))),
	  m_mapID(MushroomTown)
{
}

void Map::respawn()
{
	// respawns movables every set interval
	if (respawnTime.getElapsedTime().asSeconds() >= 14.f)
	{
		respawnTime.restart();

		for (auto& monster : m_monsters)
			if (monster->isDead())
				monster->respawn(true);
	}
}

Map& Map::instance()
{
	static Map instance;
	return instance;
}
