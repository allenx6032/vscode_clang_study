/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#include "Mouse.hpp"
#include "RenderWindow.hpp"

namespace gameEngine {
    bool Mouse::isButtonPressed(Button button)
    {
        return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
    }

    Vector2i Mouse::getPosition()
    {
        sf::Vector2i sfmlPos = sf::Mouse::getPosition();
        return Vector2i(sfmlPos.x, sfmlPos.y);
    }

    Vector2i Mouse::getPosition(RenderWindow& relativeTo)
    {
        sf::Vector2i sfmlPos = sf::Mouse::getPosition(relativeTo.getSfmlRenderWindow());
        return Vector2i(sfmlPos.x, sfmlPos.y);
    }

    void Mouse::setPosition(const Vector2i& position)
    {
        sf::Mouse::setPosition(sf::Vector2i(position.x, position.y));
    }

    void Mouse::setPosition(const Vector2i& position, RenderWindow& relativeTo)
    {
        sf::Mouse::setPosition(sf::Vector2i(position.x, position.y), relativeTo.getSfmlRenderWindow());
    }
}