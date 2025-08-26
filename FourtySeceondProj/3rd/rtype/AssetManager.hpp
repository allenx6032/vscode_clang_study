/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "exception.hpp"
#include <any>
#include <unordered_map>

// class that will manage all the assets of the game
// developpers will be able to add assets to the manager and get them back
class AssetManager {
    public:
        AssetManager() = default;
        ~AssetManager() = default;

    public:
        /**
         * @brief Add an asset to the manager
         *
         * @param name name of the asset
         * @param asset reference to the asset
         */
        template<typename T>
        void assetAddAsset(const std::string &name, T &asset)
        {
            if (_assets.find(name) != _assets.end())
                throw gameEngine::asset::AssetAlreadyExistsException("Asset already exists");
            _assets[name] = std::any(asset);
        }

        /**
         * @brief Get an asset from the manager
         *
         * @param name name of the asset
         * @return T & a reference to the asset
         */
        template<typename T>
        T &assetGetAsset(const std::string &name)
        {
            if (_assets.find(name) == _assets.end())
                throw gameEngine::asset::AssetNotFoundException("Asset not found");
            try {
                return std::any_cast<T &>(_assets[name]);
            } catch (const std::bad_any_cast &e) {
                throw gameEngine::asset::AssetCastException("Invalid cast");
            }
        }

        /**
         * @brief Remove an asset from the manager
         *
         * @param name name of the asset
         *
         * @return a reference to the asset removed so it can be deleted
         */
        template<typename T>
        T &assetRemoveAsset(const std::string &name)
        {
            if (_assets.find(name) == _assets.end())
                throw gameEngine::asset::AssetNotFoundException("Asset not found");
            try {
                T &asset = std::any_cast<T &>(_assets[name]);
                _assets.erase(name);
                return asset;
            } catch (const std::bad_any_cast &e) {
                throw gameEngine::asset::AssetCastException("Invalid cast");
            }
        }

        /**
         * @brief Check if an asset exists
         *
         * @param name name of the asset
         * @return true if the asset exists
         * @return false if the asset doesn't exist
         */
        inline bool assetExists(const std::string &name)
        {
            return _assets.find(name) != _assets.end();
        }

        /**
         * @brief Clear the manager
         *
         * @note This will not delete all the assets, it will only remove them from the manager (their default destructor will be called)
         */
        inline void assetClear()
        {
            _assets.clear();
        }

    private:
        std::unordered_map<std::string, std::any> _assets;
};
