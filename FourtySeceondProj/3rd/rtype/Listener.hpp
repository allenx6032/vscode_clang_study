/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Vector3.hpp"
#include <sfml/SFML_Listener.hpp>

namespace gameEngine {
    class Listener {
        public:
            static void setGlobalVolume(float volume) { sf::Listener::setGlobalVolume(volume); };
            static float getGlobalVolume() { return sf::Listener::getGlobalVolume(); };
            static void setPosition(float x, float y, float z) { sf::Listener::setPosition(x, y, z); };
            static void setPosition(const Vector3f &position) { sf::Listener::setPosition(position); };
            static Vector3f getPosition() { return sf::Listener::getPosition(); };
            static void setDirection(float x, float y, float z) { sf::Listener::setDirection(x, y, z); };
            static void setDirection(const Vector3f &direction) { sf::Listener::setDirection(direction); };
            static Vector3f getDirection() { return sf::Listener::getDirection(); };
            static void setUpVector(float x, float y, float z) { sf::Listener::setUpVector(x, y, z); };
            static void setUpVector(const Vector3f &upVector) { sf::Listener::setUpVector(upVector); };
            static Vector3f getUpVector() { return sf::Listener::getUpVector(); };
    };
}
