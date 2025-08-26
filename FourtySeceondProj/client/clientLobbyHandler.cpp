/*
** EPITECH PROJECT, 2023
** lobbyHandler
** File description:
** qs
*/

#include "clientLobby.hpp"

ClientLobbyHandler::ClientLobbyHandler()
{
}

ClientLobbyHandler::~ClientLobbyHandler()
{
}

void ClientLobbyHandler::createLobby(size_t size, ClientLobbyPlayer owner, std::string name, size_t id)
{
    ClientLobby lobby(size, owner, name, id);
    _lobbies.push_back(lobby);
}

void ClientLobbyHandler::removeLobby(size_t id)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id) {
            _lobbies.erase(it);
            return;
        }
    }
}

void ClientLobbyHandler::addPlayerToLobby(size_t id, ClientLobbyPlayer player)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id) {
            it->addPlayer(std::move(player));
            return;
        }
    }
}

void ClientLobbyHandler::removePlayerFromLobby(size_t id, size_t playerId)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id) {
            it->removePlayer(playerId);
            return;
        }
    }
}

void ClientLobbyHandler::setName(size_t id, std::string name)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        if (it->getId() == id) {
            it->setName(name);
            return;
        }
    }
}

std::vector<ClientLobby> ClientLobbyHandler::getLobbies()
{
    return _lobbies;
}

ClientLobby *ClientLobbyHandler::getLobbyById(size_t id)
{
    for (auto it = _lobbies.begin(); it != _lobbies.end(); it++) {
        std::cout << "id: " << (int) it->getId() << "search: " << (int) id << std::endl;
        if (it->getId() == id) {
            return &(*it);
        }
    }
    return nullptr;
}