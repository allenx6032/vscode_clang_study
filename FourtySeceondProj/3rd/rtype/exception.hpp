/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include <exception>
#include <string>

namespace gameEngine {

    namespace ecs {
        class InvalidArgument : public std::exception {
            public:
                InvalidArgument(const std::string &message) : _message("GameEngine: ECS: " + message) {};
                ~InvalidArgument() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
        };

        class InvalidComponent: public std::exception {
            public:
                InvalidComponent(const std::string &message = "The component you tried to access is not registered") : _message("GameEngine: ECS: " + message) {};
                ~InvalidComponent() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
        };
    }

    namespace lua {
        class InvalidLuaFile : public std::exception {
            public:
                InvalidLuaFile(const std::string &message) : _message("GameEngine: LuaManager: " + message) {};
                ~InvalidLuaFile() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
        };

        class InvalidLuaFunction : public std::exception {
            public:
                InvalidLuaFunction(const std::string &message) : _message("GameEngine: LuaManager: " + message) {};
                ~InvalidLuaFunction() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
        };

        class InvalidLuaType : public std::exception {
            public:
                InvalidLuaType(const std::string &message) : _message("GameEngine: LuaManager: " + message) {};
                ~InvalidLuaType() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
        };
    }

    namespace net {
        class InvalidNetworkCall : public std::exception {
            public:
                InvalidNetworkCall(const std::string &message = "Invalid network call") : _message("GameEngine: Network: " + message) {};
                ~InvalidNetworkCall() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
        };
    }

    namespace json {
        class InvalidJsonFile : public std::exception {
            public:
                InvalidJsonFile(const std::string &message) : _message("GameEngine: JsonManager: " + message) {};
                ~InvalidJsonFile() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
        };

        class JsonFileNotFound : public std::exception {
            public:
                JsonFileNotFound(const std::string &message) : _message("GameEngine: JsonManager: " + message) {};
                ~JsonFileNotFound() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
        };

        class JsonKeyNotFound : public std::exception {
            public:
                JsonKeyNotFound(const std::string &message) : _message("GameEngine: JsonManager: " + message) {};
                ~JsonKeyNotFound() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
        };
    }

    namespace asset {
        class AssetAlreadyExistsException : public std::exception {
            public:
                AssetAlreadyExistsException(const std::string &message) : _message("GameEngine: AssetManager: " + message) {};
                ~AssetAlreadyExistsException() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;

        };

        class AssetNotFoundException : public std::exception {
            public:
                AssetNotFoundException(const std::string &message) : _message("GameEngine: AssetManager: " + message) {};
                ~AssetNotFoundException() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;

        };

        class AssetCastException : public std::exception {
            public:
                AssetCastException(const std::string &message) : _message("GameEngine: AssetManager: " + message) {};
                ~AssetCastException() = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;

        };
    }
}
