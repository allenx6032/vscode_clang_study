/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** game server
*/

#include "gameServer.hpp"

GameServer::GameServer(uint16_t port, std::string ip_adress)
{
    ge.netCreateServer(port, ip_adress);
    ge.netStartServer();
    _udpIp = ip_adress;
}

void GameServer::startLobby(size_t lobbyId)
{
   //create a ServerInstance and run it in a thread
    std::cout << "start lobby\n";
    std::cout << lobbyId << std::endl;
    Message<tcpProtocol> serverResponse;
    serverResponse.header.id = tcpProtocol::LobbyStarted;
    serverResponse << lobbyId;

    // check game type of the lobby
    bool playingPong = _lobbyHandler.getLobbyById(lobbyId)->getGame() == LobbyGame::PONG;

    if (playingPong) {
        std::cout << "creating pong server\n";
        PongServer *server = new PongServer(_udpPort, _udpIp);
        net::Message<tcpProtocol> msg = {tcpProtocol::Udp, sizeof(tcpProtocol::Udp)};
        msg << server->getGameEngine().netGetDataChannel()->getEndpoint();
        std::cout << "sending : " << server->getGameEngine().netGetDataChannel()->getEndpoint() << std::endl;
        for (auto lobby : _lobbyHandler.getLobbies()) {
            if (lobby.getId() == lobbyId) {
                for (auto player : lobby.getPlayers()) {
                    for (auto connection : ge.netGetConnections()) {
                        if (connection && connection->getId() == player->getId()) {
                            std::cout << "sentMessage\n";
                            ge.netSendTcpMessage(connection, serverResponse);
                            ge.netSendTcpMessage(connection, msg);
                            break;
                        }
                    }
                }
            }
        }

        // delete the lobby
        _lobbyHandler.removeLobby(lobbyId);
        Message<tcpProtocol> removeLobbyMsg;
        removeLobbyMsg.header.id = tcpProtocol::LobbyRemoved;
        removeLobbyMsg << lobbyId;
        ge.netSendTcpMessageToAll(removeLobbyMsg);

        //run the server in a new thread
        std::thread buff = std::thread([server]() {
            server->run();
        });
        buff.detach();
    } else {
        std::cout << "creating rtype server\n";
        ServerInstance *server;
        if (_lobbyHandler.getLobbyById(lobbyId)->_isMapSet == true)
            server =  new ServerInstance(_udpPort, _udpIp, _lobbyHandler.getLobbyById(lobbyId)->getMap(), 1);
        else
            server =  new ServerInstance(_udpPort, _udpIp);

        net::Message<tcpProtocol> msg = {tcpProtocol::Udp, sizeof(tcpProtocol::Udp)};
        msg << server->getGameEngine().netGetDataChannel()->getEndpoint();
        std::cout << "sending : " << server->getGameEngine().netGetDataChannel()->getEndpoint() << std::endl;
        for (auto lobby : _lobbyHandler.getLobbies()) {
            if (lobby.getId() == lobbyId) {
                for (auto player : lobby.getPlayers()) {
                    for (auto connection : ge.netGetConnections()) {
                        if (connection && connection->getId() == player->getId()) {
                            std::cout << "sentMessage\n";
                            ge.netSendTcpMessage(connection, serverResponse);
                            ge.netSendTcpMessage(connection, msg);
                            break;
                        }
                    }
                }
            }
        }

        // delete the lobby
        _lobbyHandler.removeLobby(lobbyId);
        Message<tcpProtocol> removeLobbyMsg;
        removeLobbyMsg.header.id = tcpProtocol::LobbyRemoved;
        removeLobbyMsg << lobbyId;
        ge.netSendTcpMessageToAll(removeLobbyMsg);

        //run the server in a new thread
        std::thread buff = std::thread([server]() {
            server->run();
        });
        buff.detach();
    }
    _udpPort++;
}

void GameServer::sendJoinToPlayer(size_t lobbyId, net::OwnedMessage<tcpProtocol> msg)
{
    Message<tcpProtocol> serverResponse;
    serverResponse.header.id = tcpProtocol::LobbyJoin;
    serverResponse << lobbyId << msg.remote.get()->getId() << _lobbyHandler.getLobbyById(lobbyId)->getGame();
    ge.netSendTcpMessage(msg.remote, serverResponse);
}

void GameServer::updateTcp()
{
    size_t lobbyId;
    size_t lobbySize;
    std::string lobbyName;
    std::string mapName;
    size_t messageCounter = 0;
    int game;
    Message<tcpProtocol> serverResponse;
    if (ge.netGetConnections().empty())
        return;
    while (!ge.netIncomingTcp().empty()) {
        auto msg = ge.netIncomingTcp().popFront();
        switch (msg.msg.header.id) {
            case tcpProtocol::LobbyCreate:
                msg.msg >> lobbySize >> lobbyName;
                _lobbyHandler.createLobby(lobbySize, *msg.remote, lobbyName);
                serverResponse.header.id = tcpProtocol::LobbyCreated;
                serverResponse << _lobbyHandler.getLobbies().back().getName() << msg.remote.get()->getName() << lobbySize << msg.remote.get()->getId() << _lobbyHandler.getLobbies().back().getId();
                ge.netSendTcpMessageToAll(serverResponse);
                lobbyId = _lobbyHandler.getLobbies().back().getId();
                sendJoinToPlayer(lobbyId, msg);
                break;
            case tcpProtocol::LobbyJoin:
                msg.msg >> lobbyId;
                if (_lobbyHandler.getLobbyById(lobbyId)->getSize() <= _lobbyHandler.getLobbyById(lobbyId)->getPlayers().size())
                    break;
                _lobbyHandler.addPlayerToLobby(lobbyId, *msg.remote);
                serverResponse.header.id = tcpProtocol::LobbyJoined;
                serverResponse << msg.remote.get()->getName() << msg.remote.get()->getId() << lobbyId;
                ge.netSendTcpMessageToAll(serverResponse);
                sendJoinToPlayer(lobbyId, msg);
                break;
            case tcpProtocol::LobbyLeave:
                msg.msg >> lobbyId;
                std::cout << "leaving lobby\n";
                _lobbyHandler.removePlayerFromLobby(lobbyId, *msg.remote);
                serverResponse.header.id = tcpProtocol::LobbyLeft;
                serverResponse << msg.remote.get()->getId() << lobbyId;
                ge.netSendTcpMessageToAll(serverResponse);
                break;
            case tcpProtocol::LobbyStart:
                msg.msg >> lobbyId;
                std::cout << "starting lobby\n";
                _lobbyHandler.startGame(lobbyId);
                startLobby(lobbyId);
                break;
            case tcpProtocol::LobbyChangeGame:
                msg.msg >> lobbyId;
                std::cout << "changing game\n";
                _lobbyHandler.changeGame(lobbyId);
                serverResponse.header.id = tcpProtocol::LobbyChangeGame;
                game = _lobbyHandler.getLobbyById(lobbyId)->getGame();
                serverResponse << game << lobbyId;
                ge.netSendTcpMessageToAll(serverResponse);
                break;
            case tcpProtocol::LobbySetName:
                msg.msg >> lobbyId >> lobbyName;
                std::cout << "setting lobby name\n";
                _lobbyHandler.setName(lobbyId, lobbyName);
                serverResponse.header.id = tcpProtocol::LobbyNameSet;
                serverResponse << lobbyName << lobbyId;
                ge.netSendTcpMessageToAll(serverResponse);
                break;
            case tcpProtocol::SetName:
                msg.msg >> lobbyName;
                msg.remote.get()->setName(lobbyName);
                break;
            case tcpProtocol::LobbySetMap:
                msg.msg >> lobbyId >> mapName;
                std::cout << "setting lobby map\n";
                _lobbyHandler.setMap(lobbyId, mapName);
            default:
                break;
        }
        messageCounter++;
    }
}

void GameServer::syncNewPlayer()
{
    if (ge.netGetConnections().size() == _nbConnected)
        return;
    for (; _nbConnected < ge.netGetConnections().size() ; _nbConnected++) {
        for (auto& lobby : _lobbyHandler.getLobbies()) {
            Message<tcpProtocol> msg;
            msg.header.id = tcpProtocol::LobbyCreated;
            msg << lobby.getName() << lobby.getOwner()->getName() << lobby.getSize() << lobby.getOwner()->getId() << lobby.getId();
            ge.netSendTcpMessage(ge.netGetConnections()[_nbConnected], msg);
            for (auto& player : lobby.getPlayers()) {
                if (player->getId() == lobby.getOwner()->getId())
                    continue;
                Message<tcpProtocol> msg;
                msg.header.id = tcpProtocol::LobbyJoined;
                msg << player->getName() << player->getId() << lobby.getId();
                ge.netSendTcpMessage(ge.netGetConnections()[_nbConnected], msg);
            }
        }
    }
}

void GameServer::run()
{
    while (1) {
        syncNewPlayer();
        updateTcp();
    }
}
