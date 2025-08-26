/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "exception.hpp"
#include "nlohmann/json.hpp"
#include <fstream>

class JsonManager {
    public:
        JsonManager() = default;
        ~JsonManager() = default;

    public:
        /**
         * @brief Load a json file
         *
         * @param path The path to the json file
         *
         * @throw gameEngine::json::InvalidJsonFile If the file does not exist or is not a json file
         */
        void jsonLoadFile(const std::string &path);

        /**
         * @brief Get a json file
         *
         * @param path The path to the json file
         *
         * @return The json file
         *
         * @throw gameEngine::json::JsonFileNotFound If the file does not exist
         */
        nlohmann::json &jsonGetFile(const std::string &path);

        /**
         * @brief Get a value from a json file
         *
         * @param path The path to the json file
         * @param args The key(s) to the value
         *
         * @return The value
         *
         * @throw gameEngine::json::JsonFileNotFound If the file does not exist
         * @throw gameEngine::json::JsonKeyNotFound If the key does not exist
         */
        template <typename T, class... Args>
        T jsonGetValue(const std::string &path, Args... args)
        {
            if (_jsonFiles.find(path) == _jsonFiles.end())
                throw gameEngine::json::JsonFileNotFound("The json file " + path + " was not found");
            return jsonGetValuePrivate<T>(_jsonFiles[path], args...);
        }

        /**
         * @brief Get a value from a json file
         *
         * @param json The json file
         * @param args The key(s) to the value
         *
         * @return The value
         *
         * @throw gameEngine::json::JsonFileNotFound If the file does not exist
         * @throw gameEngine::json::JsonKeyNotFound If the key does not exist
         */
        template <typename T, class... Args>
        T jsonGetValue(nlohmann::json &json, Args... args)
        {
            return jsonGetValuePrivate<T>(json, args...);
        }

    private:
        template <typename T, class... Args>
        T jsonGetValuePrivate(nlohmann::json &json, const std::string &key, Args... args)
        {
            if (json.find(key) == json.end())
                throw gameEngine::json::JsonKeyNotFound("The key " + key + " was not found in the json file");
            if constexpr (sizeof...(args) == 0)
                return json[key].get<T>();
            else
                return jsonGetValuePrivate<T>(json[key], args...);
        }

        // jsonGetValuePrivate overload for arrays
        template <typename T, class... Args>
        T jsonGetValuePrivate(nlohmann::json &json, const int &key, Args... args)
        {
            if (json.size() <= key)
                throw gameEngine::json::JsonKeyNotFound("The key " + std::to_string(key) + " was not found in the json file");
            if constexpr (sizeof...(args) == 0)
                return json[key].get<T>();
            else
                return jsonGetValuePrivate<T>(json[key], args...);
        }

    private:
        std::unordered_map<std::string, nlohmann::json> _jsonFiles;
};
