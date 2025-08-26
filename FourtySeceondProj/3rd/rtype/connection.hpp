#pragma once

#include "common.hpp"
#include "msg.hpp"
#include "queue.hpp"


#define SCRAMBLE_OR_1 0xDAEFC0DECAFE
#define SCRAMBLE_OR_2 0xBEEFDEADDEAD
#define SCRAMBLE_AND_1 0x0F0C0AF0EE0C0AD
#define SCRAMBLE_AND_2 0x0F0F0F0F0F0F0F0F
#define SCRAMBLE_RSHIFT 16
#define SCRAMBLE_LSHIFT 8

class Network;

namespace net
{

    template<typename T>
    class Connection : public std::enable_shared_from_this<Connection<T>> {
        public:

            Connection(owner parent, asio::io_context& asioContext, asio::ip::tcp::socket socket, Queue<OwnedMessage<T>>& qIn, std::string name = "test")
				: _asioContext(asioContext), _socket(std::move(socket)), _qMessagesIn(qIn), _name(name)
            {
                _ownerType = parent;

                if (_ownerType == owner::Server) {
                    //construct random data for handshake
                    _handshakeOut = uint64_t(std::chrono::system_clock::now().time_since_epoch().count());

                    _handshakeCheck = scrambleData(_handshakeOut);
                } else {
                    _handshakeIn = 0;
                    _handshakeOut = 0;
                    _handshakeCheck = 0;
                }
            }

            virtual ~Connection() = default;

            size_t getId() const
            {
                return id;
            }

        public:
            void connectToClient(Network *server, int userId = 0)
            {
                if (_ownerType == owner::Server) {
                    if (_socket.is_open()) {
                        id = userId;
                        //register a task to be executed asynchronously
                        writeValidation();
                        readValidation(server);
                    }
                }
            }

            void connectToServer(const asio::ip::tcp::resolver::results_type& endpoints)
            {
                //check if it's a client
                if (_ownerType == owner::Client) {
                    asio::async_connect(_socket, endpoints,
                    [this](std::error_code ec, asio::ip::tcp::endpoint endpoint)
                    {
                        if (!ec) {
                            std::cout << "Connected\n";
                            readValidation(nullptr);
                        } else {
                            std::cout << "Failed to connect to server\n";
                            _socket.close();
                        }
                    });
                }
            }

            void disconnect()
            {
                if (isConnected())
                    asio::post(_asioContext, [this]() { _socket.close();});
            }

            bool isConnected() const
            {
                return _socket.is_open();
            }

            void send(const Message<T>& msg)
            {
                asio::post(_asioContext,
                    [this, msg]()
                    {
                        bool bWritingMessage = !_qMessagesOut.empty();
                        _qMessagesOut.pushBack(msg);
                        if (!bWritingMessage)
                            writeHeader();
                    }
                );
            }

            std::string getName() const
            {
                return _name;
            }

            void setName(std::string name)
            {
                _name = name;
            }

        private:
            //ASYNC
            void readHeader()
			{
				asio::async_read(_socket, asio::buffer(&_msgTempIn.header, sizeof(MessageHeader<T>)),
					[this](std::error_code ec, std::size_t length)
					{
						if (!ec) {
							if (_msgTempIn.header.size > 0) {
								_msgTempIn.body.resize(_msgTempIn.header.size);
								readBody();
							} else
								addToIncomingMessageQueue();
						} else {
							std::cout << "[" << id << "] Read Header Fail.\n";
							_socket.close();
						}
					});
			}

            void readBody()
			{
				asio::async_read(_socket, asio::buffer(_msgTempIn.body.data(), _msgTempIn.body.size()),
					[this](std::error_code ec, std::size_t length)
					{
						if (!ec) {
							addToIncomingMessageQueue();
						} else {
							std::cout << "[" << id << "] Read Body Fail.\n";
							_socket.close();
						}
					});
			}

            void writeHeader()
			{
				asio::async_write(_socket, asio::buffer(&_qMessagesOut.front().header, sizeof(MessageHeader<T>)),
					[this](std::error_code ec, std::size_t length)
					{
						if (!ec) {
							if (_qMessagesOut.front().body.size() > 0) {
								writeBody();
							} else {
								_qMessagesOut.popFront();
								if (!_qMessagesOut.empty())
									writeHeader();
							}
						} else {
							std::cout << "[" << id << "] Write Header Fail.\n";
							_socket.close();
						}
					});
			}

            void writeBody()
			{
				asio::async_write(_socket, asio::buffer(_qMessagesOut.front().body.data(), _qMessagesOut.front().body.size()),
					[this](std::error_code ec, std::size_t length)
					{
						if (!ec) {
							_qMessagesOut.popFront();

							if (!_qMessagesOut.empty())
								writeHeader();
						} else {
							std::cout << "[" << id << "] Write Body Fail.\n";
							_socket.close();
						}
					});
			}

            void addToIncomingMessageQueue()
            {
                if (_ownerType == owner::Server)
                    _qMessagesIn.pushBack({ this->shared_from_this(), _msgTempIn});
                else
                    _qMessagesIn.pushBack({nullptr, _msgTempIn});

                readHeader();
            }

            uint64_t scrambleData(uint64_t input)
            {
                uint64_t output = input ^ SCRAMBLE_OR_1;
                output = (output & SCRAMBLE_AND_1) >> SCRAMBLE_RSHIFT | (output & SCRAMBLE_AND_2) << SCRAMBLE_LSHIFT;
                output = output ^ SCRAMBLE_OR_2;
                std::cout << "Scrambled Data: [" << input << "] -> (" << output << ")\n";
                return output;
            }

            void writeValidation()
            {
                asio::async_write(_socket, asio::buffer(&_handshakeOut, sizeof(uint64_t)),
                    [this](std::error_code ec, std::size_t length)
                    {
                        if (!ec) {
                            if (_ownerType == owner::Client)
                                readHeader();
                        } else {
                            _socket.close();
                        }
                    }
                );
            }

            void readValidation(Network *server = nullptr)
            {
                asio::async_read(_socket, asio::buffer(&_handshakeIn, sizeof(uint64_t)),
                    [this, server](std::error_code ec, std::size_t length)
                    {
                        if (!ec) {
                            if (_ownerType == owner::Server) {
                                if (_handshakeIn == _handshakeCheck) {
                                    std::cout << "[" << id << "] Client Validated\n";
                                    // if (server)
                                    //     server->onClientValidation(this->shared_from_this());
                                    readHeader();
                                } else {
                                    std::cout << "[" << id << "] sus amogus inpostor sugoma\n";
                                    _socket.close();
                                }
                            } else {
                                _handshakeOut = scrambleData(_handshakeIn);
                                writeValidation();
                            }
                        } else {
                            std::cout << "[" << id << "] Client Disconnected (Read Validation)\n";
                            _socket.close();
                        }
                    }
                );
            }

        protected:
            asio::io_context& _asioContext;
            asio::ip::tcp::socket _socket;
            Queue<Message<T>> _qMessagesOut;
            Queue<OwnedMessage<T>>& _qMessagesIn;
            Message<T> _msgTempIn;
            owner _ownerType = owner::Server;
            size_t id = 0;
            std::string _name;

            uint64_t _handshakeOut = 0;
            uint64_t _handshakeIn = 0;
            uint64_t _handshakeCheck = 0;
    };
}
