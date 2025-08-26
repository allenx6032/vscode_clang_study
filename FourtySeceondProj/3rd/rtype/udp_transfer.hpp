// protocol and use inspired by the goat aka Erwan gonsales

#pragma once

#include "common.hpp"
#include "msg.hpp"
#include "queue.hpp"
#include "udp_msg.hpp"

namespace net {
    template<typename T>
    class UdpTransfer {
    public:
        UdpTransfer(asio::io_context &asioContext, Queue<OwnedMessageUdp<T>> &qin, std::string adress, size_t port = 0)
            : _asioContext(asioContext),
            _socket(asioContext, asio::ip::udp::endpoint(asio::ip::address::from_string(adress), port)),
            _qMessagesIn(qin)
            {
                std::cout << "UdpTransfer created\n";
                std::cout << "endpoint: " << _socket.local_endpoint() << std::endl;
                readUdp();
            }

        virtual ~UdpTransfer() = default;

    public:
        void sendTo(MessageUdp <T> &msg, asio::ip::udp::endpoint target) {
            msg.calculateChecksum();
            asio::post(_asioContext,
                        [this, msg, target]() {
                            bool bWritingMessage = !_qMessagesOut.empty();
                            _qMessagesOut.pushBack(OwnedMessageUdp<T>{msg, target});
                            if (!bWritingMessage) {
                                sendUdp();
                            }
                        }
            );
        }

        void sendAll(MessageUdp <T> &msg) {
            msg.calculateChecksum();
            asio::post(_asioContext,
                [this, msg]() {
                    bool bWritingMessage = !_qMessagesOut.empty();
                    for (auto &endpoint: _endpoints) {
                        _qMessagesOut.pushBack(OwnedMessageUdp<T>{msg, endpoint});
                    }
                    if (!bWritingMessage) {
                        sendUdp();
                    }
                }
            );
        }

        void sendAllExcept(const MessageUdp <T> &msg, asio::ip::udp::endpoint &except) {
            msg.calculateChecksum();
            asio::post(_asioContext,
                [this, msg, except]() {
                    bool bWritingMessage = !_qMessagesOut.empty();
                    std::cout << _endpoints.size() << std::endl;
                    for (auto endpoint: _endpoints) {
                        if (endpoint.address() != except.address() || endpoint.port() != except.port())
                            _qMessagesOut.pushBack(OwnedMessageUdp<T>{msg, endpoint});
                    }
                    if (!bWritingMessage && !_qMessagesOut.empty()) {
                        sendUdp();
                    }
                }
            );
        }

        void addClient(const asio::ip::udp::endpoint &endpoint) {
            std::cout << "adding client: " << endpoint << std::endl;
            _endpoints.insert(endpoint);
            std::cout << "added client\n";
        }

        asio::ip::udp::endpoint getEndpoint() {
            return _socket.local_endpoint();
        }

    private:
        //ASYNC
        void readUdp() {
            _socket.async_receive_from(asio::buffer(&_msgTempIn, MSG_SIZE), _buffer_endpoint,
                [this](std::error_code ec, std::size_t length) {
                    if (!ec) {
                        addToIncomingMessageQueue();
                    } else {
                        std::cout << "Read Udp Fail.\n";
                        std::cout << ec.message() << std::endl;
                        std::cout << _buffer_endpoint << std::endl;
                        _socket.close();
                    }
                });
        }

        void sendUdp() {
                _socket.async_send_to(asio::buffer(&_qMessagesOut.front().msg, MSG_SIZE), _qMessagesOut.front().remote_endpoint,
                    [this](std::error_code ec, std::size_t length) {
                        if (!ec) {
                            _qMessagesOut.popFront();
                            if (!_qMessagesOut.empty())
                                sendUdp();
                        } else {
                            std::cout << "Send Udp Fail.\n";
                            std::cout << ec.message() << std::endl;
                            std::cout << _qMessagesOut.front().remote_endpoint << std::endl;
                            _socket.close();
                        }
                    });
        }

        void addToIncomingMessageQueue()
        {
            if (_msgTempIn.verifyChecksum() == true) {
                _endpoints.insert(_buffer_endpoint);
                _qMessagesIn.pushBack(OwnedMessageUdp<T>{_msgTempIn, _buffer_endpoint});
            } else {
                std::cout << "checksum failed, found corrupted packages\n";
            }
            readUdp();
        }

        asio::ip::udp::socket &getSocket()
        {
            return _socket;
        }

    protected:
        asio::io_context &_asioContext;
        asio::ip::udp::socket _socket;
        std::set<asio::ip::udp::endpoint> _endpoints;
        asio::ip::udp::endpoint _buffer_endpoint;
        Queue<OwnedMessageUdp<T>> _qMessagesOut;
        Queue<OwnedMessageUdp<T>>& _qMessagesIn;
        MessageUdp <T> _msgTempIn;
    };
}
