/*
** EPITECH PROJECT, 2023
** header
** File description:
** da
*/

#pragma once
#include "rtype/gameEngine.hpp"
#include "rtype/init.hpp"
#include "rtype/systemCustom2.hpp"
#include "rtype/entityCreation.hpp"
#include "pongServerSystem.hpp"

#define SECOND_IN_MS 1000
#define FRAMERATE 60
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class PongServer {
    public:
        PongServer(uint16_t port, std::string ip_adress = "127.0.0.1");
        ~PongServer() = default;

    public:
        void run();

        GameEngine &getGameEngine() { return ge; }

    private:
        void resyncGame();

        void managePlayerMoveAsk(net::OwnedMessageUdp<udpProtocol> &msg);

        void updateNetwork();

        void init();

    private:
        GameEngine ge;

        int _scorePlayer1 = 0;
        int _scorePlayer2 = 0;

        size_t _ballEntity;
        size_t _player1Entity;
        size_t _player2Entity;

        std::thread _threadContext;
        std::map<asio::ip::udp::endpoint, size_t> _udpClients;
        std::vector<size_t> _players;
        uint16_t _udpPort = 4242;
        std::string _udpIp = "127.0.0.1";
};
