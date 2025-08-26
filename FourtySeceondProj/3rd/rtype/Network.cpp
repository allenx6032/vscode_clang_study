/*
** EPITECH PROJECT, 2023
** network
** File description:
** cpp file for network in game engine
*/

#include "network.hpp"

void Network::netCreateServer(uint16_t port, std::string ipAdress)
{
    if (_ownerType == owner::Client)
        throw gameEngine::net::InvalidNetworkCall();
    _asioAcceptor = std::make_unique<asio::ip::tcp::acceptor>(_asioContext, asio::ip::tcp::endpoint(asio::ip::address::from_string(ipAdress), port));
    std::cout << "Waiting on " << ipAdress << std::endl;
    _ipAdress = ipAdress;
    _ownerType = owner::Server;
}

bool Network::netStartServer()
{
    if (_ownerType == owner::Client)
        throw gameEngine::net::InvalidNetworkCall();
    try {
        netWaitClientConnection();
        _threadContext = std::thread([this]() { _asioContext.run(); });
    } catch (std::exception& e) {
        std::cerr << "[SERVER] Exception: " << e.what() << '\n';
        return false;
    }
    std::cout << "[SERVER] Started\n";
    return true;
}

void Network::netStopServer()
{
    if (_ownerType == owner::Client)
        throw gameEngine::net::InvalidNetworkCall();
    _asioContext.stop();
    if (_threadContext.joinable())
        _threadContext.join();
    std::cout << "[SERVER] Stopped\n";
}

void Network::netOnClientValidation(std::shared_ptr<Connection<tcpProtocol>> client)
{
    _validated++;
}

void Network::netWaitClientConnection()
{
    if (_ownerType == owner::Client)
        throw gameEngine::net::InvalidNetworkCall();
    _asioAcceptor->async_accept(
        [this](std::error_code ec, asio::ip::tcp::socket socket) {
            if (!ec) {
                std::cout << "[SERVER] New Connection: " << socket.remote_endpoint() << '\n';
                std::shared_ptr<Connection<tcpProtocol>> newconn = std::make_shared<Connection<tcpProtocol>>(owner::Server, _asioContext, std::move(socket), _qMessagesIn);
                _deqConnections.push_back(std::move(newconn));
                _deqConnections.back()->connectToClient(this, idCounter++);
                std::cout << "[" << _deqConnections.back()->getId() << "] Connection Approved\n";
            } else {
                std::cout << "[SERVER] New Connection Error: " << ec.message() << '\n';
            }
            netWaitClientConnection();
        });
}

bool Network::netConnectToServer(const std::string& host, const size_t port)
{
    if (_ownerType == owner::Server)
        throw gameEngine::net::InvalidNetworkCall();
    try {
        asio::ip::tcp::resolver resolver(_asioContext);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

        std::shared_ptr<Connection<tcpProtocol>> newcon = std::make_shared<Connection<tcpProtocol>>(owner::Client, _asioContext, asio::ip::tcp::socket(_asioContext), _qMessagesIn);
        _deqConnections.push_back(std::move(newcon));
        _deqConnections.back()->connectToServer(endpoints);
        _threadContext = std::thread([this]() { _asioContext.run(); });
    } catch (std::exception& e) {
        std::cerr << "[CLIENT] Exception: " << e.what() << '\n';
        if (!_deqConnections.empty())
            _deqConnections.pop_back();
        return false;
    }
    std::cout << "[CLIENT] Started\n";
    _ownerType = owner::Client;
    return true;
}

void Network::netDisconnect()
{
    if (_ownerType == owner::Server)
        throw gameEngine::net::InvalidNetworkCall();
    if (netIsConnected())
        _deqConnections.front()->disconnect();

    _asioContext.stop();
    if (_threadContext.joinable())
        _threadContext.join();
    _deqConnections.clear();
    _ownerType = owner::None;
    std::cout << "[CLIENT] Disconnected\n";
}

bool Network::netIsConnected()
{
    if (_ownerType == owner::Server)
        throw gameEngine::net::InvalidNetworkCall();
    if (_deqConnections.empty())
        return false;
    return _deqConnections.front()->isConnected();
}

Queue<OwnedMessage<tcpProtocol>>& Network::netIncomingTcp()
{
    return _qMessagesIn;
}

void Network::netSendTcpMessage(std::shared_ptr<Connection<tcpProtocol>> peer, const Message<tcpProtocol>& msg)
{
    if (peer && peer->isConnected()) {
        peer->send(msg);
    } else {
        peer.reset();
        // _deqConnections.erase(std::remove(_deqConnections.begin(), _deqConnections.end(), peer), _deqConnections.end());
    }
}

void Network::netSendTcpMessageToAll(const Message<tcpProtocol>& msg)
{
    // bool invalidClientExists = false;
    for (auto& client : _deqConnections) {
        if (client && client->isConnected()) {
            client->send(msg);
        } else {
            client.reset();
            // invalidClientExists = true;
        }
    }
    // if (invalidClientExists)
    //     _deqConnections.erase(std::remove(_deqConnections.begin(), _deqConnections.end(), nullptr), _deqConnections.end());
}

std::deque<std::shared_ptr<Connection<tcpProtocol>>> &Network::netGetConnections()
{
    return _deqConnections;
}

void Network::netCreateDataChannel(std::string ipAdress, uint16_t port)
{
    _dataChannel = std::make_unique<net::UdpTransfer<udpProtocol>>(this->_asioContext, _udpMessagesIn, ipAdress, port);
    std::cout << "dataChannel created : " << _dataChannel->getEndpoint() << std::endl;
}

void Network::netUdpSend(net::MessageUdp<udpProtocol>& msg, asio::ip::udp::endpoint peer)
{
    if (_dataChannel)
        _dataChannel->sendTo(msg, std::move(peer));
}

void Network::netUdpSendAll(net::MessageUdp<udpProtocol>& msg)
{
    if (_dataChannel)
        _dataChannel->sendAll(msg);
}

net::Queue<net::OwnedMessageUdp<udpProtocol>>& Network::netIncomingUdp()
{
    return _udpMessagesIn;
}

std::unique_ptr<net::UdpTransfer<udpProtocol>>& Network::netGetDataChannel()
{
    return _dataChannel;
}

int Network::netGetValidated() const
{
    return _validated;
}

void Network::netAddClientUdp(asio::ip::udp::endpoint peer)
{
    _dataChannel->addClient(peer);
}
