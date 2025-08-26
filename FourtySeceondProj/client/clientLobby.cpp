/*
** EPITECH PROJECT, 2023
** lobby classes cpp
** File description:
** yes i know , update : nevermind
*/

#include "clientLobby.hpp"

ClientLobby::ClientLobby(size_t size, ClientLobbyPlayer owner, std::string name, size_t id) :
    _size(size),
    _id(id),
    _owner(owner),
    _name(name)
{
    _players.push_back(owner);
}

ClientLobby::~ClientLobby()
{
}

void ClientLobby::setSize(size_t size)
{
    _size = size;
}

size_t ClientLobby::getSize() const
{
    return _size;
}

void ClientLobby::setId(size_t id)
{
    _id = id;
}

size_t ClientLobby::getId() const
{
    return _id;
}

void ClientLobby::setPlayers(std::vector<ClientLobbyPlayer> players)
{
    _players = players;
}

std::vector<ClientLobbyPlayer> ClientLobby::getPlayers()
{
    return _players;
}

void ClientLobby::setName(std::string name)
{
    _name = name;
}

std::string ClientLobby::getName() const
{
    return _name;
}

void ClientLobby::display()
{
    std::cout << "Lobby name: " << _name << std::endl;
    std::cout << "Lobby size: " << _size << std::endl;
    std::cout << "Lobby id: " << _id << std::endl;
    std::cout << "Lobby owner: " << _owner.getName() << std::endl;
    std::cout << "Lobby players: " << std::endl;
    int i = 0;
    for (auto player : _players) {
        i++;
        std::cout << "Player " << i << ": ";
        std::cout << player.getName() << std::endl;
    }
}

void ClientLobby::addPlayer(ClientLobbyPlayer player)
{
    _players.push_back(player);
    display();
}

void ClientLobby::removePlayer(size_t getId)
{
    for (auto it = _players.begin(); it != _players.end(); it++) {
        if (it->getId() == getId) {
            _players.erase(it);
            return;
        }
    }
}

void ClientLobby::setOwner(ClientLobbyPlayer owner)
{
    _owner = owner;
}

ClientLobbyPlayer ClientLobby::getOwner() const
{
    return _owner;
}