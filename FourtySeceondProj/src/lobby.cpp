/*
** EPITECH PROJECT, 2023
** lobby
** File description:
** lobby Handling class
*/

#include "lobby.hpp"

Lobby::Lobby(size_t size, Connection<tcpProtocol> &owner, std::string name, size_t id) :
    _size(size),
    _id(id),
    _status(WAITING),
    _owner(&owner),
    _name(name)
{
    _players.push_back(&owner);
}

Lobby::~Lobby()
{
}

void Lobby::addPlayer(Connection<tcpProtocol> &player)
{
    _players.push_back(&player);
}

void Lobby::removePlayer(Connection<tcpProtocol> &player)
{
    _players.erase(std::remove(_players.begin(), _players.end(), &player), _players.end());
}

void Lobby::startGame()
{
    _status = INGAME;
}

void Lobby::changeGame()
{
    if (_game == LobbyGame::RTYPE)
        _game = LobbyGame::PONG;
    else
        _game = LobbyGame::RTYPE;
}

void Lobby::setName(std::string name)
{
    _name = name;
}

void Lobby::setStatus(LobbyStatus status)
{
    _status = status;
}

LobbyGame Lobby::getGame() const
{
    return _game;
}

size_t Lobby::getSize() const
{
    return _size;
}

std::vector<Connection<tcpProtocol> *> Lobby::getPlayers() const
{
    return _players;
}

Connection<tcpProtocol> *Lobby::getOwner() const
{
    return _owner;
}

std::string Lobby::getName() const
{
    return _name;
}

size_t Lobby::getId() const
{
    return _id;
}

void Lobby::setMap(std::string map)
{
    _map = std::move(map);
    _isMapSet = true;
}

std::string Lobby::getMap() const
{
    return _map;
}