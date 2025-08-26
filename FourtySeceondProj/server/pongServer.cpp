/*
** EPITECH PROJECT, 2023
** header
** File description:
** da
*/

#include "pongServer.hpp"

PongServer::PongServer(uint16_t port, std::string ip_adress)
{
    srand(time(NULL));
    ge.netCreateDataChannel(ip_adress, port);
    _threadContext = std::thread([this]() { ge._asioContext.run(); });
    _udpIp = ip_adress;
}

void PongServer::managePlayerMoveAsk(net::OwnedMessageUdp<udpProtocol> &msg)
{
    std::cout << "PongPlayerAskMove" << std::endl;
    pong_player_move_ask_t playerMoveAsk;
    msg.msg >> playerMoveAsk;
    pong_player_move_t playerMove;
    if (playerMoveAsk.id != 1 && playerMoveAsk.id != 2)
        return;
    playerMove.id = playerMoveAsk.id;
    if (playerMoveAsk.move == 1) {
        playerMove.vely = 600;
        if (playerMoveAsk.id == 1) {
            auto &playerVel = ge.ecsGetComponents<component::Velocity>()[_player1Entity];
            playerVel._vely = 600;
        } else {
            auto &playerVel = ge.ecsGetComponents<component::Velocity>()[_player2Entity];
            playerVel._vely = 600;
        }
    } else if (playerMoveAsk.move == -1) {
        playerMove.vely = -600;
        if (playerMoveAsk.id == 1) {
            auto &playerVel = ge.ecsGetComponents<component::Velocity>()[_player1Entity];
            playerVel._vely = -600;
        } else {
            auto &playerVel = ge.ecsGetComponents<component::Velocity>()[_player2Entity];
            playerVel._vely = -600;
        }
    } else {
        playerMove.vely = 0;
        if (playerMoveAsk.id == 1) {
            auto &playerVel = ge.ecsGetComponents<component::Velocity>()[_player1Entity];
            playerVel._vely = 0;
        } else {
            auto &playerVel = ge.ecsGetComponents<component::Velocity>()[_player2Entity];
            playerVel._vely = 0;
        }
    }
    net::MessageUdp<udpProtocol> msgToSend;
    msgToSend.header.id = udpProtocol::PongPlayerMove;
    msgToSend << playerMove;
    ge.netUdpSendAll(msgToSend);
}

void PongServer::resyncGame()
{
    Entity player1 = ge.ecsEntityFromIndex(_player1Entity);
    pong_player_resync_t player1Resync;
    player1Resync.id = 1;
    player1Resync.posy = ge.ecsGetComponents<component::Transform>()[player1]._posy;
    net::MessageUdp<udpProtocol> msgToSend;
    msgToSend.header.id = udpProtocol::PongResync;
    msgToSend << player1Resync;
    ge.netUdpSendAll(msgToSend);

    Entity player2 = ge.ecsEntityFromIndex(_player2Entity);
    pong_player_resync_t player2Resync;
    player2Resync.id = 2;
    player2Resync.posy = ge.ecsGetComponents<component::Transform>()[player2]._posy;
    net::MessageUdp<udpProtocol> msgToSend2;
    msgToSend2.header.id = udpProtocol::PongResync;
    msgToSend2 << player2Resync;
    ge.netUdpSendAll(msgToSend2);

    Entity ball = ge.ecsEntityFromIndex(_ballEntity);
    pong_ball_t ballResync;
    ballResync.posx = ge.ecsGetComponents<component::Transform>()[ball]._posx;
    ballResync.posy = ge.ecsGetComponents<component::Transform>()[ball]._posy;
    ballResync.velx = ge.ecsGetComponents<component::Velocity>()[ball]._velx;
    ballResync.vely = ge.ecsGetComponents<component::Velocity>()[ball]._vely;
    net::MessageUdp<udpProtocol> msgToSend3;
    msgToSend3.header.id = udpProtocol::PongBallMove;
    msgToSend3 << ballResync;
    ge.netUdpSendAll(msgToSend3);

    pong_score_t score;
    score.scorePlayer1 = _scorePlayer1;
    score.scorePlayer2 = _scorePlayer2;
    net::MessageUdp<udpProtocol> msgToSend4;
    msgToSend4.header.id = udpProtocol::PongScore;
    msgToSend4 << score;
    ge.netUdpSendAll(msgToSend4);
}

void PongServer::updateNetwork()
{
    if (!ge.netGetDataChannel())
        return;
    while (!ge.netIncomingUdp().empty()) {
        std::cout << "message received" << std::endl;
        net::OwnedMessageUdp<udpProtocol> msg = ge.netIncomingUdp().popFront();
        switch (msg.msg.header.id) {
            case udpProtocol::PongPlayerAskMove:
                managePlayerMoveAsk(msg);
                break;
            default:
                break;
        }
    }
}

void PongServer::run()
{
    init();

    // Ball
    Entity ball = createBall(ge, true);
    _ballEntity = ball;

    // Player 1 (left)
    Entity player1 = createPlayerLeft(ge, true);
    _player1Entity = player1;

    // Player 2 (right)
    Entity player2 = createPlayerRight(ge, true);
    _player2Entity = player2;

    // Borders
    std::vector<Entity> borders = createBorder(ge, true);

    ge.timeSetInterval([this]() {
        resyncGame();
    }, 1000);
    ge.timeStartTick();

    while (1) {
        auto startFrame = std::chrono::high_resolution_clock::now();

        // handle network data
        updateNetwork();

        ge.ecsRunSystems();

        auto endFrame = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - startFrame);
        if (duration.count() < SECOND_IN_MS / FRAMERATE)
            std::this_thread::sleep_for(std::chrono::milliseconds(SECOND_IN_MS / FRAMERATE - duration.count()));
    }
}

void PongServer::init()
{
    setUpComponents(ge);
    ge.ecsRegisterComponent<component::ColisionBox>();
    ge.ecsRegisterComponent<component::Player>();
    ge.ecsRegisterComponent<component::Border>();
    ge.ecsRegisterComponent<component::Ball>();
    ge.ecsRegisterComponent<component::Text>();
    ge.ecsRegisterComponent<component::Score>();

    ge.ecsAddSystem<component::Transform,
                    component::Velocity>(updatePosSystem);
    ge.ecsAddSystem<component::Player,
                    component::Border,
                    component::Transform,
                    component::ColisionBox>(playerColisionSystem);
    ge.ecsAddSystem<component::Ball,
                    component::Border,
                    component::Player,
                    component::Transform,
                    component::ColisionBox>(ballColisionSystemServer, _scorePlayer1, _scorePlayer2);
}