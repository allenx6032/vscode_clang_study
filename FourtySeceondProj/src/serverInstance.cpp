/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** game server
*/

#include "serverInstance.hpp"

ServerInstance::ServerInstance(uint16_t port, std::string ip_adress, std::string map, int isMapSet)
{
    srand(time(NULL));
    ge.netCreateDataChannel(ip_adress, port);
    _threadContext = std::thread([this]() { ge._asioContext.run(); });
    _udpIp = ip_adress;

    if (isMapSet == 0) {
        std::ifstream file("Server/levels/level1.txt");
        if (!file || !file.is_open())
            return;
        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> row;
            for (int i = 0; i < line.size(); i++) {
                row.push_back(line[i] - '0');
            }
            _map.push_back(row);
        }
        file.close();
        std::cout << "here LLALALALAL\n";
    } else {
        std::vector<int> row;
        for (int i = 0; i < map.size(); i++) {
            if (map[i] == '\n') {
                _map.push_back(row);
                row.clear();
            } else {
                row.push_back(map[i] - '0');
            }
        }
    }
}

void ServerInstance::manageNetCreatePlayer(net::OwnedMessageUdp<udpProtocol> &msg)
{
    net::MessageUdp<udpProtocol> msgToSend;
    player_t player;

    std::cout << "first message received\n";
    _udpClients[msg.remote_endpoint] = curr_id;
    msgToSend.header.id = udpProtocol::CreatePlayer;
    Entity playerEntity = ge.ecsSpawnEntity();
    _players.push_back(playerEntity);
    int playerSprite = _players.size() - 1;
    player = { (float) (rand() % PLAYER_SPAWN_X) , (float) ((playerSprite+1) * PLAYER_SPAWN_Y), curr_id, playerSprite};
    playerCreation(playerEntity, curr_id, player);
    msgToSend << player;
    ge.netUdpSend(msgToSend, msg.remote_endpoint);
    sendAllPlayers();
    curr_id++;
}

void ServerInstance::updateUdp()
{
    //update game
    pos_t pos;
    vel_t vel;
    if (!ge.netGetDataChannel())
        return;
    while (!ge.netIncomingUdp().empty()) {
        std::cout << "message received\n";
        net::OwnedMessageUdp<udpProtocol> msg = ge.netIncomingUdp().popFront();
        net::MessageUdp<udpProtocol> msgToSend;
        switch (msg.msg.header.id)
        {
            case udpProtocol::CreatePlayer:
                manageNetCreatePlayer(msg);
                break;
            case udpProtocol::CreateBullet:
                msg.msg >> pos;
                createBulletFromMessage(curr_id, msg);
                curr_id++;
                break;
            case udpProtocol::PlayerMove:
                msg.msg >> vel;
                msgToSend.header.id = udpProtocol::PlayerMove;
                msgToSend << vel;
                if (isMoveValid(vel)) {
                    ge.netUdpSendAll(msgToSend);
                    movePlayer(_udpClients[msg.remote_endpoint], vel);
                }
                break;
            default:
                break;
        }
    }
}

void ServerInstance::resyncGame()
{
    //refresh players
    for (auto it = _udpClients.begin(); it != _udpClients.end(); it++) {
        try {
            if (it->second == 0)
                continue;
            Entity entity = ge.ecsEntityFromIndex(getFromIdComponent(ge, it->second));
            auto &tra = ge.ecsGetComponents<component::Transform>()[entity];
            // find the pos of entity in _players
            int playerSprite = std::find(_players.begin(), _players.end(), entity) - _players.begin();
            player_t pos = { tra._posx, tra._posy, it->second, playerSprite};
            net::MessageUdp<udpProtocol> msgToSend;
            msgToSend.header.id = udpProtocol::Resync;
            msgToSend << pos;
            ge.netUdpSendAll(msgToSend);
        } catch (std::exception &e) {
            it->second = 0;
            std::cerr << "player not found" << std::endl;
        }
    }
    //refresh enemies
    for (auto &enemy : ge.ecsGetComponents<component::IsEnemy>()) {
        if (!ge.ecsGetComponents<component::Transform>().has(enemy.first))
            continue;
        auto &tra = ge.ecsGetComponents<component::Transform>()[enemy.first];
        auto const &id = ge.ecsGetComponents<component::Id>()[enemy.first];
        pos_t pos = { tra._posx, tra._posy, id._id};
        net::MessageUdp<udpProtocol> msgToSend;
        msgToSend.header.id = udpProtocol::Resync;
        msgToSend << pos;
        ge.netUdpSendAll(msgToSend);
    }
}

bool ServerInstance::isMoveValid(vel_t vel)
{
    if (vel.velx < -PLAYER_SPEED || vel.velx > PLAYER_SPEED)
        return false;
    if (vel.vely < -PLAYER_SPEED || vel.vely > PLAYER_SPEED)
        return false;
    if (!hasIdComponent(ge, vel.id))
        return false;
    return true;
}

void ServerInstance::movePlayer(size_t id, vel_t vel)
{
    Entity tmp = ge.ecsEntityFromIndex(getFromIdComponent(ge, id));
    auto &tra = ge.ecsGetComponents<component::Velocity>()[tmp];
    auto &transforms = ge.ecsGetComponents<component::Transform>()[tmp];
    tra._velx = vel.velx;
    tra._vely = vel.vely;
}

void ServerInstance::createBullet(float posx, float posy, size_t id)
{
    Entity bullet = ge.ecsSpawnEntity();

    component::Transform pos = { posx, posy, 0, 0, 0, 0, BULLET_SCALE, BULLET_SCALE, BULLET_SCALE };
    ge.ecsAddComponent(bullet, pos);

    component::Velocity vel = { BULLET_SPEED, 0, 0 };
    ge.ecsAddComponent(bullet, vel);

    component::ColisionBoxCustom col = { 0, 0, 0, BULLET_WIDTH * BULLET_SCALE, BULLET_HEIGHT * BULLET_SCALE, 0, true, component::ColisionBoxCustom::Layer::MISSILE,COLLISION_MATRIX };
    ge.ecsAddComponent(bullet, col);

    component::Bullet bulletComp = { BULLET_DAMAGE };
    ge.ecsAddComponent(bullet, bulletComp);

    component::Id idComp = { id };
    ge.ecsAddComponent(bullet, idComp);

    // std::cout << "bullet created\n";
}

void ServerInstance::createBulletFromMessage(size_t id, net::OwnedMessageUdp<udpProtocol> msg)
{

    try {
        net::MessageUdp<udpProtocol> msgToSend;
        pos_t pos;
        if (_udpClients[msg.remote_endpoint] == 0)
            return;
        Entity tmp = ge.ecsEntityFromIndex(getFromIdComponent(ge, _udpClients[msg.remote_endpoint]));
        auto &tra = ge.ecsGetComponents<component::Transform>()[tmp];
        createBullet(tra._posx + (PLAYER_WIDTH * 3), tra._posy, id);
        msgToSend.header.id = udpProtocol::CreateBullet;
        pos = { tra._posx + (PLAYER_WIDTH * 3), tra._posy, id };
        msgToSend << pos;
        std::cout << "sending bullet" << std::endl;
        ge.netUdpSendAll(msgToSend);
    } catch (std::exception &e) {
        std::cerr << "player not found" << std::endl;
    }
}

void ServerInstance::sendAllPlayers()
{
    net::MessageUdp<udpProtocol> msgToSend;
    for (auto const &entity : ge.ecsGetComponents<component::Id>()) {
        if (!ge.ecsGetComponents<component::Transform>().has(entity.first))
            continue;
        auto &tra = ge.ecsGetComponents<component::Transform>()[entity.first];
        // find the pos of entity in _players
        int playerSprite = std::find(_players.begin(), _players.end(), entity.first) - _players.begin();
        player_t pos = { tra._posx, tra._posy, entity.second._id, playerSprite };
        msgToSend.header.id = udpProtocol::ConnectedPlayer;
        msgToSend << pos;
        ge.netUdpSendAll(msgToSend);
    }
}

void ServerInstance::playerCreation(Entity player, size_t _id, player_t pos)
{
    component::Transform transform = { pos.posx, pos.posy, 0, 0, 0, 0, 3, 3, 3 };
    ge.ecsAddComponent(player, transform);
    component::Velocity vel = { 0, 0, 0 };
    ge.ecsAddComponent(player, vel);
    component::ColisionBoxCustom col = { 0, 0, 0, PLAYER_WIDTH * 3, PLAYER_HEIGHT * 3, 0, false, component::ColisionBoxCustom::Layer::PLAYER,COLLISION_MATRIX };
    ge.ecsAddComponent(player, col);
    component::Unmovable unmovable = { true };
    ge.ecsAddComponent(player, unmovable);
    component::OutlineBox2D outlineBox(PLAYER_WIDTH * 3, PLAYER_HEIGHT * 3);
    ge.ecsAddComponent(player, outlineBox);
    component::Id id = { _id };
    ge.ecsAddComponent(player, id);
}

void ServerInstance::generateEnemy(GameEngine &ge, int posx, int posy, int typeEnemy)
{
    Entity enemy = ge.ecsSpawnEntity();

    component::Transform pos = { (float)posx, (float)posy, 0,
                                0, 0, 0,
                                -3, 3, 3 };
    ge.ecsAddComponent(enemy, pos);

    component::Unmovable unmovable = { true };
    ge.ecsAddComponent(enemy, unmovable);

    component::Id id = { curr_id };
    ge.ecsAddComponent(enemy, id);
    curr_id++;

    if (typeEnemy == 1) {
        component::EnemyType type = {component::EnemyType::Type::SIMPLE};
        ge.ecsAddComponent(enemy, type);
        component::Velocity vel = {-120, 60, 0};
        ge.ecsAddComponent(enemy, vel);
        component::ColisionBoxCustom col = { ENEMY_WIDTH * -3, 0, 0, ENEMY_WIDTH * 3, ENEMY_HEIGHT * 3, 0, false, component::ColisionBoxCustom::Layer::ENEMY, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::Health health = { ENEMY_HEALTH };
        ge.ecsAddComponent(enemy, health);
    } else if (typeEnemy == 2) {
        component::EnemyType type = {component::EnemyType::Type::MECHA};
        ge.ecsAddComponent(enemy, type);
        component::Velocity vel = {-120, 0, 0};
        ge.ecsAddComponent(enemy, vel);
        component::ColisionBoxCustom col = { ENEMY_WIDTH * -3, 0, 0, ENEMY_WIDTH * 3, ENEMY_HEIGHT * 3, 0, false, component::ColisionBoxCustom::Layer::ENEMY, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::Health health = { ENEMY_HEALTH };
        ge.ecsAddComponent(enemy, health);
    } else if (typeEnemy == 4) {
        component::ColisionBoxCustom col = { ENEMY_WIDTH * -3, 0, 0, ENEMY_WIDTH * 3, ENEMY_HEIGHT * 3, 0, false, component::ColisionBoxCustom::Layer::OBSTACLE, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::Velocity vel = { -120, 0, 0 };
        ge.ecsAddComponent(enemy, vel);
    } else if (typeEnemy == 3) {
        component::EnemyType type = {component::EnemyType::Type::OTHER};
        ge.ecsAddComponent(enemy, type);
        component::Velocity vel = { -120, 240, 0 };
        ge.ecsAddComponent(enemy, vel);
        component::ColisionBoxCustom col = { ENEMY_WIDTH * -3, 0, 0, ENEMY_WIDTH * 3, ENEMY_HEIGHT * 3, 0, false, component::ColisionBoxCustom::Layer::ENEMY, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::Health health = { ENEMY_HEALTH };
        ge.ecsAddComponent(enemy, health);
    } else if (typeEnemy == 5) {
        component::EnemyType type = {component::EnemyType::Type::BOSS};
        ge.ecsAddComponent(enemy, type);
        component::Velocity vel = {-500, 0, 0};
        ge.ecsAddComponent(enemy, vel);
        component::ColisionBoxCustom col = { 260 * -3, 0, 0, 260 * 3, 142 * 3, 0, false, component::ColisionBoxCustom::Layer::ENEMY, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::Health health = { 2500 };
        ge.ecsAddComponent(enemy, health);
    } else if (typeEnemy == -1) {
        component::EnemyType type = {component::EnemyType::Type::MISSILE};
        ge.ecsAddComponent(enemy, type);
        component::Velocity vel = {-300, 300, 0};
        ge.ecsAddComponent(enemy, vel);
        component::ColisionBoxCustom col = { 34 * -3, 0, 0, 34 * 3, 34 * 3, 0, false, component::ColisionBoxCustom::Layer::ENEMY, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::Health health = { 25 };
        ge.ecsAddComponent(enemy, health);
    }

    component::IsEnemy isEnemy;
    ge.ecsAddComponent(enemy, isEnemy);

    component::hasTouch hasTouch;
    ge.ecsAddComponent(enemy, hasTouch);

    net::MessageUdp<udpProtocol> msgToSend;
    pos_t posToSend = { pos._posx, pos._posy, id._id };
    msgToSend.header.id = udpProtocol::CreateEnnemy;
    msgToSend << posToSend;
    std::cout << typeEnemy << std::endl;
    msgToSend << typeEnemy;
    ge.netUdpSendAll(msgToSend);
}

void ServerInstance::initSystems()
{
    ge.ecsAddSystem<component::Transform,
            component::Velocity>(updatePosSystem);
    ge.ecsAddSystem<component::Transform,
            component::Velocity,
            component::EnemyType,
            component::hasTouch,
            component::IsEnemy>(enemyPattern);
    ge.ecsAddSystem<component::Transform,
            component::ColisionBoxCustom>(enemyHitPlayerSystem);
    ge.ecsAddSystem<component::Transform,
            component::ColisionBoxCustom,
            component::Velocity,
            component::Unmovable>(colisionSystemCustom);
    ge.ecsAddSystem<component::Transform,
            component::ColisionBoxCustom,
            component::Bullet,
            component::Health>(takeHitSystem, this->_spawnEnemyNumber);
    ge.ecsAddSystem<component::Transform,
            component::Bullet>(deleteOutOfMapBullets);
    ge.ecsAddSystem<component::ToDelete>(garbageCollectorSystem);
}

void ServerInstance::run()
{
    static int curr_index = 0;

    if (curr_index >= _map.size())
        curr_index = 0;
    initLuaScripts(ge);
    setUpComponents(ge);
    initSystems();
    ge.timeSetInterval([this]() {
        resyncGame();
    }, PLAYER_REFRESH);
    ge.timeSetInterval([this]() {
        for (int y = 0; y < _map[0].size(); y++) {
            int _type = _map[curr_index][y];
            if (_type > 0) {
                std::cout << "generating enemy " << _type << std::endl;
                generateEnemy(this->ge, 2400, y * 82, _type);
            }
        }
        curr_index++;
        if (curr_index >= _map.size())
            curr_index = 0;
        // for (int i = 0; i < this->_spawnEnemyNumber; i++)
        //     generateEnemy(this->ge, 1600, randInt(200, 800));
    }, ENEMY_REFRESH);
    ge.timeSetInterval([this]() {
        for (auto &enemy : ge.ecsGetComponents<component::IsEnemy>()) {
            if (!ge.ecsGetComponents<component::Transform>().has(enemy.first) ||
                !ge.ecsGetComponents<component::EnemyType>().has(enemy.first))
                continue;
            auto &type = ge.ecsGetComponents<component::EnemyType>()[enemy.first];
            if (type._type != component::EnemyType::Type::BOSS)
                continue;
            auto &tra = ge.ecsGetComponents<component::Transform>()[enemy.first];
            auto &vel = ge.ecsGetComponents<component::Velocity>()[enemy.first];
            if (vel._velx != 0)
                continue;
            int randomOut = randInt(1, 6);

            int posX = 0;
            int posY = 0;
            switch (randomOut) {
                case 1:
                    posX = 1134;
                    posY = 700;
                    break;
                case 2:
                    posX = 1498;
                    posY = 640;
                    break;
                case 3:
                    posX = 1650;
                    posY = 956;
                    break;
                case 4:
                    posX = 974;
                    posY = 730;
                    break;
                case 5:
                    posX = 1222;
                    posY = 946;
                    break;
                case 6:
                    posX = 1400;
                    posY = 920;
                    break;
            }
            generateEnemy(this->ge, posX, posY, -1);
        }
    }, 1000);
    ge.timeStartTick();
    while (1) {
        auto startFrame = std::chrono::high_resolution_clock::now();

        updateUdp();
        ge.ecsRunSystems();

        auto endFrame = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - startFrame);
        if (duration.count() < SECOND_IN_MS / FRAMERATE)
            std::this_thread::sleep_for(std::chrono::milliseconds(SECOND_IN_MS / FRAMERATE - duration.count()));
    }
}
