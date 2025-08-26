/*
** EPITECH PROJECT, 2023
** lobby
** File description:
** lobby
*/

#pragma once
#include "rtype/gameEngine.hpp"

enum LobbyStatus {
    WAITING,
    INGAME
};

enum LobbyGame {
    RTYPE,
    PONG
};

class Lobby {

    public:
        Lobby(size_t size, Connection<tcpProtocol> &owner, std::string name, size_t id);
        ~Lobby();

        void addPlayer(Connection<tcpProtocol> &player);
        void removePlayer(Connection<tcpProtocol> &player);
        void startGame();
        void changeGame();
        void setName(std::string name); //rename function
        void setStatus(LobbyStatus status);
        void setMap(std::string mapName);

        LobbyGame getGame() const;
        size_t getSize() const;
        std::vector<Connection<tcpProtocol> *> getPlayers() const;
        Connection<tcpProtocol> *getOwner() const;
        std::string getName() const;
        size_t getId() const;
        std::string getMap() const;

        bool _isMapSet = false;
    private:
        size_t _size;
        size_t _id;
        LobbyStatus _status;
        LobbyGame _game = LobbyGame::RTYPE;
        std::vector<Connection<tcpProtocol> *> _players;
        Connection<tcpProtocol> *_owner;
        std::string _name;
        std::string _map;
};

class ServerLobbyHandler {
    public:
        ServerLobbyHandler();
        ~ServerLobbyHandler();

        void createLobby(size_t size, Connection<tcpProtocol> &owner, std::string name);
        void removeLobby(size_t id);
        void addPlayerToLobby(size_t id, Connection<tcpProtocol> &player);
        void removePlayerFromLobby(size_t id, Connection<tcpProtocol> &player);
        void startGame(size_t id);
        void changeGame(size_t id);
        void setName(size_t id, std::string name);
        void setMap(size_t id, std::string mapName);

        std::vector<Lobby> getLobbies();
        Lobby *getLobbyById(size_t id);

    private:
        std::string mapName;
        std::vector<Lobby> _lobbies;
        size_t _currId = 0;
};