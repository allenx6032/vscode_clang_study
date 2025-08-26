/*
** EPITECH PROJECT, 2023
** lobby class
** File description:
** lobby in client
*/

#pragma once
#include <iostream>
#include <vector>


class ClientLobbyPlayer {
    public:
        ClientLobbyPlayer(std::string name, size_t id);
        ~ClientLobbyPlayer();

        void setName(std::string name);

        std::string getName() const;

        void setId(size_t id);

        size_t getId() const;

        void setReady(bool ready);

        bool isReady() const;

    private:
        std::string _name;
        size_t _id;
        bool _isReady;
};

class ClientLobby {
    public:
        ClientLobby(size_t size, ClientLobbyPlayer owner, std::string name, size_t id);
        ~ClientLobby();

    public:
        void setSize(size_t size);

        size_t getSize() const;

        void setId(size_t id);

        size_t getId() const;

        void setPlayers(std::vector<ClientLobbyPlayer> players);

        void addPlayer(ClientLobbyPlayer player);

        void removePlayer(size_t id);

        std::vector<ClientLobbyPlayer> getPlayers();

        void setName(std::string name);

        std::string getName() const;

        void display();

        void setOwner(ClientLobbyPlayer owner);

        ClientLobbyPlayer getOwner() const;


    private:
        size_t _size;
        size_t _id;
        std::vector<ClientLobbyPlayer> _players;
        ClientLobbyPlayer _owner;
        std::string _name;
};

class ClientLobbyHandler {
    public:
        ClientLobbyHandler();
        ~ClientLobbyHandler();

        void createLobby(size_t size, ClientLobbyPlayer owner, std::string name, size_t id);
        void removeLobby(size_t id);
        void addPlayerToLobby(size_t id, ClientLobbyPlayer player);
        void removePlayerFromLobby(size_t id, size_t playerId);
        void setName(size_t id, std::string name);

        std::vector<ClientLobby> getLobbies();
        ClientLobby *getLobbyById(size_t id);

    private:
        std::vector<ClientLobby> _lobbies;
        size_t _currId = 0;
};