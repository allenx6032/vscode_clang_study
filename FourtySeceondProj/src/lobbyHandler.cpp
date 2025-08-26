/*
** EPITECH PROJECT, 2023
** lobbyHandler
** File description:
** lobbies handling class
*/

#include "lobby.hpp"

ServerLobbyHandler::ServerLobbyHandler()
{
}

ServerLobbyHandler::~ServerLobbyHandler()
{
}

void ServerLobbyHandler::createLobby(size_t size, Connection<tcpProtocol> &owner, std::string name)
{
    _lobbies.push_back(Lobby(size, owner, std::move(name), _currId++));
}

void ServerLobbyHandler::removeLobby(size_t id)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id) {
            _lobbies.erase(it);
            return;
        }
    }
}

void ServerLobbyHandler::addPlayerToLobby(size_t id, Connection<tcpProtocol> &player)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id) {
            it->addPlayer(player);
            return;
        }
    }
}

void ServerLobbyHandler::removePlayerFromLobby(size_t id, Connection<tcpProtocol> &player)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id) {
            it->removePlayer(player);
            return;
        }
    }
}

void ServerLobbyHandler::startGame(size_t id)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id) {
            it->startGame();
            return;
        }
    }
}

void ServerLobbyHandler::changeGame(size_t id)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id) {
            it->changeGame();
            return;
        }
    }
}

void ServerLobbyHandler::setName(size_t id, std::string name)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id) {
            it->setName(name);
            return;
        }
    }
}

std::vector<Lobby> ServerLobbyHandler::getLobbies()
{
    return _lobbies;
}

Lobby *ServerLobbyHandler::getLobbyById(size_t id)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id)
            return &(*it);
    }
    return nullptr;
}

void ServerLobbyHandler::setMap(size_t id, std::string mapName)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id) {
            it->setMap(mapName);
            return;
        }
    }
}
