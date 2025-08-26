/*
** EPITECH PROJECT, 2023
** gameClient
** File description:
** game
*/

#pragma once
#include "rtype/gameEngine.hpp"
#include "rtype/init.hpp"
#include "rtype/systemCustom2.hpp"
#include "rtype/entityCreation.hpp"

class PongClient {
    public:
        PongClient() = delete;
        PongClient(gameEngine::RenderWindow &window, GameEngine &ge) : _window(window), ge(ge) {};
        ~PongClient() = default;

    public:
        void run(size_t playerId);

    private:
        void handleInput();

        void handleNetwork();

        void playerUpdateMove(net::OwnedMessageUdp<udpProtocol> &msg);

        void ballUpdateMove(net::OwnedMessageUdp<udpProtocol> &msg);

        void scoreUpdate(net::OwnedMessageUdp<udpProtocol> &msg);

        void syncPlayerPos(net::OwnedMessageUdp<udpProtocol> &msg);

        void init();

    private:
        GameEngine &ge;
        gameEngine::RenderWindow &_window;
        gameEngine::Event _event;

        bool _isFocused = false;

        size_t _ballEntity;
        size_t _player1Entity;
        size_t _player2Entity;

        int _scorePlayer1 = 0;
        int _scorePlayer2 = 0;

        int _oldMove = 0;

        size_t _playerId = 1;

        gameEngine::Sound _sound;
        sf::SoundBuffer _buffer;
};
