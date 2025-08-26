/*
** EPITECH PROJECT, 2023
** gameClient
** File description:
** game
*/

#pragma once

#include "rtype/gameEngine.hpp"
#include "pongClient.hpp"
#include "rtype/init.hpp"
#include "rtype/systemCustom.hpp"
#include "clientLobby.hpp"
#include "textBox.hpp"
#include <sfml/SFML_Graphics.hpp>
#include <chrono>

using namespace std::chrono_literals;

#define TCP_PORT 6000

#define SECOND_IN_MS 1000
#define FRAMERATE 60
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define PLAYER_WIDTH 33
#define PLAYER_HEIGHT 17
#define PLAYER_SPEED 600

#define BULLET_WIDTH 145
#define BULLET_HEIGHT 60
#define BULLET_SPEED 1800

#define ENEMY_WIDTH 36
#define ENEMY_HEIGHT 34

class GameClient {
    public:
        GameClient() = delete;
        GameClient(gameEngine::RenderWindow& window);

        ~GameClient() = default;

    public:

        void updateTcp();

        void init(std::string ip, size_t port, std::string name);

        void waitGameStart();

        void paralaxCreation(std::string path);

        void updateLobbyPlayers();

        void playerCreation(player_t position, Entity &player, bool isSelf = false);

        void syncPlayer(net::OwnedMessageUdp<udpProtocol> &msg);

        void initSystems();

        void connectionScreen();

        void lobbyScreen(std::string);

        void inLobbyScreen();

        void createBullet(pos_t bullet_pos);

        void handlePlayer(Entity &player, int &bulletTime);

        void run();

        void movePlayer(size_t id, vel_t vel);

        void resyncEntityWithId(net::OwnedMessageUdp<udpProtocol> &msg);

        void generateEnemy(GameEngine &ge, pos_t networkPos, int typeEnemy);

        void updateGame(Entity &player);

        void destroyEntity(destroy_t &destroy, Entity &player);

        void sendMap(std::string mapName);

        Entity createExplosion(component::Transform &pos);

    private:
        GameEngine ge;
        bool _isFocused = true;
        size_t _myId = 0;
        gameEngine::RenderWindow &_window;
        ClientLobbyHandler _lobbyHandler;
        std::vector<Entity> _players;
        ClientLobby *_currentLobby = nullptr;
        vel_t oldVel = {0, 0, 0};
        bool _inLobby = false;
        bool _inGame = false;
        std::vector<Entity> _lobbies;
        size_t lobbyX = 590;
        size_t lobbyY = 240;
        size_t playerY = 240;
        bool _playingPong = false;
        bool _rtypeIsAlive = false;
        sf::Music _music;
};
