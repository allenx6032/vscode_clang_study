/*
** EPITECH PROJECT, 2023
** header
** File description:
** da
*/

#include "rtype/gameEngine.hpp"
#include "rtype/init.hpp"
#include "lobby.hpp"
#include "serverInstance.hpp"
#include "pongServer.hpp"
#include "systemServer.hpp"
#include "rtype/systemCustom.hpp"
#include "rtype/api.hpp"
#include <map>
#include <algorithm>

#define FRAMERATE 60

#define SECOND_IN_MS 1000
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define PLAYER_WIDTH 33
#define PLAYER_HEIGHT 17
#define PLAYER_SPEED 600
#define PLAYER_REFRESH 100
#define PLAYER_SPAWN_X 800
#define PLAYER_SPAWN_Y 200

#define BULLET_WIDTH 145
#define BULLET_HEIGHT 60
#define BULLET_SPEED 1800
#define BULLET_DAMAGE 25
#define BULLET_SCALE 0.5

#define ENEMY_WIDTH 36
#define ENEMY_HEIGHT 34
#define ENEMY_SPAWN_X_1 1600
#define ENEMY_SPAWN_X_2 1900
#define ENEMY_SPAWN_Y_1 200
#define ENEMY_SPAWN_Y_2 800
#define ENEMY_HEALTH 100
#define ENEMY_REFRESH 1000

class GameServer
{

    public:
        GameServer(uint16_t port, std::string ip_adress = "127.0.0.1");
        ~GameServer() = default;

    public:
        void updateTcp();

        void startLobby(size_t lobbyId);

        void run();

        void syncNewPlayer();

        void sendJoinToPlayer(size_t lobbyId, net::OwnedMessage<tcpProtocol> msg);

    private:
        GameEngine ge;
        size_t curr_id = 1;

        uint16_t _udpPort = 4242;
        std::string _udpIp = "127.0.0.1";
        // std::thread _gameThread;
        ServerLobbyHandler _lobbyHandler;
        size_t _nbConnected = 0;
};
