#pragma once
#include "common.hpp"

namespace net
{
    template <typename T>
    struct MessageHeader {
        T id{}; // {} = default value / constructor for class
        size_t size = 0;
    };

    template <typename T>
    struct Message {
        MessageHeader<T> header;
        std::vector<uint8_t> body;

        size_t size() const
        {
            return body.size();
        }

        friend std::ostream& operator << (std::ostream& os, const Message<T>& msg)
        {
            os << "ID: " << (int) msg.header.id << " Size: " << msg.header.size << std::endl;
            return os;
        }

       template <typename DataType>
        friend Message<T>& operator << (Message<T>& msg, const DataType& data)
        {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be handled");
            size_t oldSize = msg.body.size();
            msg.body.resize(oldSize + sizeof(DataType));
            std::memcpy(msg.body.data() + oldSize, &data, sizeof(DataType));
            msg.header.size = msg.size();
            return msg;
        }

        friend Message<T>& operator << (Message<T>& msg, const std::string& data)
        {
            size_t oldSize = msg.body.size();
            size_t dataSize = data.size();
            msg.body.resize(oldSize + sizeof(size_t) + dataSize);
            std::memcpy(msg.body.data() + oldSize, &dataSize, sizeof(size_t));
            std::memcpy(msg.body.data() + oldSize + sizeof(size_t), data.data(), dataSize);
            msg.header.size = msg.size();
            return msg;
        }

        template<typename DataType>
        friend Message<T>& operator >> (Message<T>& msg, DataType& data)
        {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from vector");
            size_t i = msg.body.size() - sizeof(DataType);
            std::memcpy(static_cast<void *> (&data), static_cast<const void *> (msg.body.data() + i), sizeof(DataType));

            msg.body.resize(i);
            msg.header.size = msg.size();
            return msg;
        }

        friend Message<T>& operator >> (Message<T>& msg, std::string& data)
        {
            size_t dataSize = 0;
            std::memcpy(&dataSize, msg.body.data(), sizeof(size_t));
            data.resize(dataSize);
            std::memcpy(data.data(), msg.body.data() + sizeof(size_t), dataSize);
            msg.body.erase(msg.body.begin(), msg.body.begin() + sizeof(size_t) + dataSize);
            msg.header.size = msg.size();
            return msg;
        } //string have to be at the 
    };

    template <typename T>
    class Connection;

    template <typename T>
    struct OwnedMessage {
        std::shared_ptr<Connection<T>> remote = nullptr;
        Message<T> msg;

        friend std::ostream& operator<<(std::ostream & os, const OwnedMessage Message)
        {
            os << Message.msg;
            return os;
        }
    };
}
