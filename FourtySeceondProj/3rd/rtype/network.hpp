/*
** EPITECH PROJECT, 2023
** Network encapsulation
** File description:
** Game Engine
*/

#pragma once
#include "common.hpp"
#include "connection.hpp"
#include "exception.hpp"
#include "msg.hpp"
#include "protocol.hpp"
#include "queue.hpp"
#include "udp_msg.hpp"
#include "udp_transfer.hpp"

using namespace net;

class Network {
    public:
        Network() {};
        ~Network() = default;


    public:
        //serverSide
        void netCreateServer(uint16_t port, std::string ipAdress);

        bool netStartServer();

        void netStopServer();

        void netWaitClientConnection();

        void netOnClientValidation(std::shared_ptr<Connection<tcpProtocol>> client);
        //end of serverSide

        //clientSide

        bool netConnectToServer(const std::string& host, const size_t port);

        void netDisconnect();

        bool netIsConnected();


        //end of clientSide

        //common

        Queue<OwnedMessage<tcpProtocol>>& netIncomingTcp();

        void netSendTcpMessage(std::shared_ptr<Connection<tcpProtocol>> peer, const Message<tcpProtocol>& msg);

        void netSendTcpMessageToAll(const Message<tcpProtocol>& msg);

        //update ?

        std::deque<std::shared_ptr<Connection<tcpProtocol>>> &netGetConnections();

        //end of common

        //udp

        void netCreateDataChannel(std::string ipAdress, uint16_t port);

        void netUdpSend(net::MessageUdp<udpProtocol>& msg, asio::ip::udp::endpoint peer);

        void netUdpSendAll(net::MessageUdp<udpProtocol>& msg);

        net::Queue<net::OwnedMessageUdp<udpProtocol>>& netIncomingUdp();

        std::unique_ptr<net::UdpTransfer<udpProtocol>>& netGetDataChannel();

        void netAddClientUdp(asio::ip::udp::endpoint peer);

        int netGetValidated() const;

    public:
        asio::io_context _asioContext;
    private:

        owner _ownerType = owner::None;
        //tcp
        Queue<OwnedMessage<tcpProtocol>> _qMessagesIn;
        std::deque<std::shared_ptr<Connection<tcpProtocol>>> _deqConnections;
        std::thread _threadContext;
        std::unique_ptr<asio::ip::tcp::acceptor> _asioAcceptor = nullptr;
        size_t idCounter = 0;
        std::string _ipAdress;
        //end of tcp

        //udp
        net::Queue<net::OwnedMessageUdp<udpProtocol>> _udpMessagesIn;
        std::unique_ptr<net::UdpTransfer<udpProtocol>> _dataChannel = nullptr;
        int _validated = 0;
        //end of udp
};