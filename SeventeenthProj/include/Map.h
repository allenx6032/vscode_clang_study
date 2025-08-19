#pragma once

#include "Monster.h"
#include "staticObject.h"
#include "Portal.h"
#include "NPC.h"

class Map
{
public:
    //----------------------
    enum Maps
    {
        Menu,
        MushroomTown,
        SmallForest,
        SplitRoad,
        WestAmherst,
        Amherst,
        WestSouthperry,
        Southperry,
        Max,
    };
    //----------------------
    static Map& instance();

    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;


    std::unique_ptr<Player>& player() { return m_player; }
    std::vector<std::unique_ptr<NPC>>& npcs() { return m_npcs; }
    std::vector<std::unique_ptr<Monster>>& monsters() { return m_monsters; }
    std::vector<std::unique_ptr<staticObject>>& unmovables() { return m_unmovables; }
    std::vector<std::unique_ptr<Portal>>& portals() { return m_portals; }
    int& mapWidth() { return m_mapWidth; }
    int& mapHeight() { return m_mapHeight; }
    int& mapID() { return m_mapID; }
    std::unique_ptr<sf::Sprite>& background() { return m_background; }
    std::unique_ptr<sf::Sprite>& map() { return m_map; }
    std::unique_ptr<sf::Sound>& music() { return m_music; }
    void respawn();

private:
    Map();
    int m_mapID;                                                    // each map has its own ID number to identify it
    std::unique_ptr<Player> m_player;                               // our player
    std::vector<std::unique_ptr<NPC>> m_npcs;                       // NPC = Non-Playable Character
    std::vector<std::unique_ptr<Monster>> m_monsters;               // monsters
    std::vector<std::unique_ptr<staticObject>> m_unmovables;        // ground, wall, etc
    std::vector<std::unique_ptr<Portal>> m_portals;                 // map portals (transport to another map)
    std::unique_ptr<sf::Sprite> m_background;                       // 2nd layer of map
    std::unique_ptr<sf::Sprite> m_map;                              // 1st layer of map
    std::unique_ptr<sf::Sound> m_music;                             // BGM (background music)
    int m_mapWidth;                                                 // tile count per row
    int m_mapHeight;                                                // tile count per column
    sf::Clock respawnTime;                                          // helps respawning objects on time
};
