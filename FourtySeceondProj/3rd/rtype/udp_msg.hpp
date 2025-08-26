#pragma once
#include "common.hpp"

#define MSG_SIZE 1024

namespace net {

    template <typename T>
    struct MessageHeaderUdp {
        T id{}; // {} = default value / constructor for class
        size_t size = 0;
        uint32_t checksum = 0;
    };

    template <typename T>
    struct MessageUdp {
        MessageHeaderUdp<T> header;
        std::array<uint8_t, MSG_SIZE - sizeof(header)> body = {};

        void calculateChecksum() {
            uint32_t totalSize = sizeof(MessageHeaderUdp<T>) + body.size();
            header.checksum = 0;
            uint32_t* packetData = reinterpret_cast<uint32_t*>(this);
            uint32_t sum = 0;

            for (uint32_t i = 0; i < totalSize / sizeof(uint32_t); i++) {
                sum += packetData[i];
            }

            header.checksum = sum;
        }

        bool verifyChecksum() const {
            uint32_t totalSize = sizeof(MessageHeaderUdp<T>) + body.size();
            uint32_t sum = 0;

            for (uint32_t i = 0; i < totalSize / sizeof(uint32_t); i++) {
                sum += reinterpret_cast<const uint32_t*>(this)[i];
            }

            uint32_t receivedChecksum = header.checksum;
            return (sum - receivedChecksum) == receivedChecksum;
        }

        size_t size() const
        {
            return body.size() + sizeof(header);
        }

        friend std::ostream& operator << (std::ostream& os, const MessageUdp<T>& msg)
        {
            os << "ID: " << (int) msg.header.id << " Size: " << msg.header.size << std::endl;
            return os;
        }

        template <typename DataType>
        friend MessageUdp<T>& operator << (MessageUdp<T>& msg, const DataType& data)
        {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be handled");
            std::memcpy(msg.body.data(), &data, sizeof(DataType));
            return msg;
        }

        template<typename DataType>
        friend MessageUdp<T>& operator >> (MessageUdp<T>& msg, DataType& data)
        {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from array");
            std::memcpy(&data, msg.body.data(), sizeof(DataType));
            return msg;
        }
    };

    template <typename T>
    struct OwnedMessageUdp {
        MessageUdp<T> msg;
        asio::ip::udp::endpoint remote_endpoint;

        friend std::ostream& operator<<(std::ostream & os, const OwnedMessageUdp message)
        {
            os << message.msg;
            return os;
        }
    };
}