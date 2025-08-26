/*
** EPITECH PROJECT, 2023
** lobby players
** File description:
** lobby players
*/

#include "clientLobby.hpp"

ClientLobbyPlayer::ClientLobbyPlayer(std::string name, size_t id) :
    _name(name),
    _id(id),
    _isReady(false)
{
}

ClientLobbyPlayer::~ClientLobbyPlayer()
{
}

void ClientLobbyPlayer::setName(std::string name)
{
    _name = name;
}

std::string ClientLobbyPlayer::getName() const
{
    return _name;
}

void ClientLobbyPlayer::setId(size_t id)
{
    _id = id;
}

size_t ClientLobbyPlayer::getId() const
{
    return _id;
}

void ClientLobbyPlayer::setReady(bool ready)
{
    _isReady = ready;
}

bool ClientLobbyPlayer::isReady() const
{
    return _isReady;
}


