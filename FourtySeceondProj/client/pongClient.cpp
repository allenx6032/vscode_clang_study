/*
** EPITECH PROJECT, 2023
** gameClient
** File description:
** game
*/

#include "pongClient.hpp"

#define FRAMERATE 60
#define SECOND_IN_MS 1000
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void PongClient::handleInput()
{
    if (_isFocused == false)
        return;

    if (gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Z) || gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Up)) {
        if (_oldMove != -1) {
            std::cout << "Move UP" << std::endl;

            pong_player_move_ask_t playerAskMove;
            playerAskMove.id = _playerId;
            playerAskMove.move = -1;

            net::MessageUdp<udpProtocol> msgToSend;
            msgToSend.header.id = udpProtocol::PongPlayerAskMove;
            msgToSend << playerAskMove;
            ge.netUdpSendAll(msgToSend);

            if (_playerId == 1) {
                auto &playerVels = ge.ecsGetComponents<component::Velocity>()[_player1Entity];
                playerVels._vely = -600;
            } else {
                auto &playerVels = ge.ecsGetComponents<component::Velocity>()[_player2Entity];
                playerVels._vely = -600;
            }

            _oldMove = -1;
        }
    } else if (gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::S) || gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Down)) {
        if (_oldMove != 1) {
            std::cout << "Move DOWN" << std::endl;

            pong_player_move_ask_t playerAskMove;
            playerAskMove.id = _playerId;
            playerAskMove.move = 1;

            net::MessageUdp<udpProtocol> msgToSend;
            msgToSend.header.id = udpProtocol::PongPlayerAskMove;
            msgToSend << playerAskMove;
            ge.netUdpSendAll(msgToSend);

            if (_playerId == 1) {
                auto &playerVels = ge.ecsGetComponents<component::Velocity>()[_player1Entity];
                playerVels._vely = 600;
            } else {
                auto &playerVels = ge.ecsGetComponents<component::Velocity>()[_player2Entity];
                playerVels._vely = 600;
            }

            _oldMove = 1;
        }
    } else {
        if (_oldMove != 0) {
            std::cout << "Move NONE" << std::endl;

            pong_player_move_ask_t playerAskMove;
            playerAskMove.id = _playerId;
            playerAskMove.move = 0;

            net::MessageUdp<udpProtocol> msgToSend;
            msgToSend.header.id = udpProtocol::PongPlayerAskMove;
            msgToSend << playerAskMove;
            ge.netUdpSendAll(msgToSend);

            if (_playerId == 1) {
                auto &playerVels = ge.ecsGetComponents<component::Velocity>()[_player1Entity];
                playerVels._vely = 0;
            } else {
                auto &playerVels = ge.ecsGetComponents<component::Velocity>()[_player2Entity];
                playerVels._vely = 0;
            }

            _oldMove = 0;
        }
    }
}

void PongClient::playerUpdateMove(net::OwnedMessageUdp<udpProtocol> &msg)
{
    pong_player_move_t playerMove;
    msg.msg >> playerMove;
    if (playerMove.id != 1 && playerMove.id != 2)
        return;

    auto &playerVels = ge.ecsGetComponents<component::Velocity>();

    if (playerMove.id == 1)
        playerVels[_player1Entity]._vely = playerMove.vely;
    else
        playerVels[_player2Entity]._vely = playerMove.vely;
}

void PongClient::ballUpdateMove(net::OwnedMessageUdp<udpProtocol> &msg)
{
    pong_ball_t ballMove;
    msg.msg >> ballMove;

    auto &ballTrans = ge.ecsGetComponents<component::Transform>()[_ballEntity];
    auto &ballVel = ge.ecsGetComponents<component::Velocity>()[_ballEntity];

    ballTrans._posx = ballMove.posx;
    ballTrans._posy = ballMove.posy;
    ballVel._velx = ballMove.velx;
    ballVel._vely = ballMove.vely;
}

void PongClient::scoreUpdate(net::OwnedMessageUdp<udpProtocol> &msg)
{
    pong_score_t score;
    msg.msg >> score;

    _scorePlayer1 = score.scorePlayer1;
    _scorePlayer2 = score.scorePlayer2;
}

void PongClient::syncPlayerPos(net::OwnedMessageUdp<udpProtocol> &msg)
{
    pong_player_resync_t playerResync;
    msg.msg >> playerResync;
    if (playerResync.id != 1 && playerResync.id != 2)
        return;

    auto &playerTrans = ge.ecsGetComponents<component::Transform>();

    if (playerResync.id == 1)
        playerTrans[_player1Entity]._posy = playerResync.posy;
    else
        playerTrans[_player2Entity]._posy = playerResync.posy;
}

void PongClient::handleNetwork()
{
    while (!ge.netIncomingUdp().empty()) {
        net::OwnedMessageUdp<udpProtocol> msg = ge.netIncomingUdp().popFront();
        switch (msg.msg.header.id) {
            case udpProtocol::PongPlayerMove:
                playerUpdateMove(msg);
                break;
            case udpProtocol::PongBallMove:
                ballUpdateMove(msg);
                break;
            case udpProtocol::PongScore:
                scoreUpdate(msg);
                break;
            case udpProtocol::PongResync:
                syncPlayerPos(msg);
                break;
            default:
                break;
        }
    }
}

void PongClient::run(size_t playerId)
{
    init();
    _playerId = playerId + 1;
    std::cout << "Player id: " << _playerId + 1 << std::endl;

    // Dotted line
    createDottedLine(ge);

    // Ball
    Entity ball = createBall(ge);
    _ballEntity = ball;

    // Player 1 (left)
    Entity player1 = createPlayerLeft(ge);
    _player1Entity = player1;

    // Player 2 (right)
    Entity player2 = createPlayerRight(ge);
    _player2Entity = player2;

    // Borders
    std::vector<Entity> borders = createBorder(ge);

    // Scores
    gameEngine::Font font;
    font.loadFromFile("r-type.ttf");
    std::vector<Entity> scores = createScore(ge, font);

    ge.ecsRunSingleSystem<component::Sprite, component::Texture>(loadSpriteTexture);

    while (_window.isOpen()) {
        auto startFrame = std::chrono::high_resolution_clock::now();

        while (_window.pollEvent(_event)) {
            if (_event.type == gameEngine::Event::Closed) {
                ge.netDisconnect();
                _window.close();
            }
            if (_event.type == gameEngine::Event::LostFocus)
                _isFocused = false;
            if (_event.type == gameEngine::Event::GainedFocus)
                _isFocused = true;
        }

        handleInput();

        _window.clear();

        if (ge.netIsConnected() == false) {
            _window.close();
            break;
        }
        handleNetwork();

        ge.ecsRunSystems();

        auto endFrame = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - startFrame);
        if (duration.count() < SECOND_IN_MS / FRAMERATE)
            std::this_thread::sleep_for(std::chrono::milliseconds(SECOND_IN_MS / FRAMERATE - duration.count()));
        _window.display();
    }
}

void PongClient::init()
{
    setUpComponents(ge);
    ge.ecsRegisterComponent<component::ColisionBox>();
    ge.ecsRegisterComponent<component::Player>();
    ge.ecsRegisterComponent<component::Border>();
    ge.ecsRegisterComponent<component::Ball>();
    ge.ecsRegisterComponent<component::Text>();
    ge.ecsRegisterComponent<component::Score>();

    gameEngine::Listener::setPosition(WINDOW_WIDTH / 2, 0, WINDOW_HEIGHT / 2);

    _buffer.loadFromFile("assets/Pong/sound/pongs.wav");

    _sound.setBuffer(_buffer);
    _sound.setVolume(500);
    _sound.setMinDistance(5);
    _sound.setAttenuation(0.1);
    _sound.setPitch(1);

    ge.ecsClearSystems();

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
                    component::ColisionBox>(ballColisionSystem, _sound);
    ge.ecsAddSystem<component::Transform,
                    component::Sprite>(refreshSpriteSystem);
    ge.ecsAddSystem<component::Transform,
                    component::Score,
                    component::Text>(refreshScoreSystem, _scorePlayer1, _scorePlayer2);
    ge.ecsAddSystem<component::Sprite,
                    component::Drawable>(drawSprite, _window);
    ge.ecsAddSystem<component::Text,
                    component::Score,
                    component::Drawable>(drawScoreSystem, _window);
}
