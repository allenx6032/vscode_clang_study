#include "rtype/gameEngine.hpp"
#include "systemServer.hpp"
#include "rtype/systemCustom.hpp"
#include "rtype/init.hpp"
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

class ServerInstance
{

    public:
        ServerInstance(uint16_t port, std::string ip_adress = "127.0.0.1", std::string map = "", int isMapSet = 0);
        ~ServerInstance() = default;

    private:
        void manageNetCreatePlayer(net::OwnedMessageUdp<udpProtocol> &msg);

    public:
        void updateUdp();

        void resyncGame();

        bool isMoveValid(vel_t vel);

        void movePlayer(size_t id, vel_t vel);

        void createBullet(float posx, float posy, size_t id);

        void createBulletFromMessage(size_t id, net::OwnedMessageUdp<udpProtocol> msg);

        void sendAllPlayers();

        void playerCreation(Entity player, size_t _id, player_t pos);

        int randInt(int min, int max) { return rand() % (max - min + 1) + min; }

        void generateEnemy(GameEngine &gen, int posx, int posy, int typeEnemy);

        void initSystems();

        void run();

        GameEngine &getGameEngine() { return ge; }

    private:
        GameEngine ge;
        size_t curr_id = 1;
        int gameStarted = 0;
        int _spawnEnemyNumber = 1;
        std::thread _threadContext;
        std::vector<std::vector<int>> _map;
        std::map<asio::ip::udp::endpoint, size_t> _udpClients;
        std::vector<size_t> _players;
        uint16_t _udpPort = 4242;
        std::string _udpIp = "127.0.0.1";
};
