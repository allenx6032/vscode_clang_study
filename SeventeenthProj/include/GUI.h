#pragma once

#include "Map.h"

class GUI
{
public:
    GUI(const sf::Texture& texture, const sf::Vector2f& location,
        const sf::Vector2f& size);

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleEvents(sf::RenderWindow& window) = 0;
    bool closed() { return m_closed; }
    
    virtual ~GUI() = default;

protected:
    sf::Sprite m_GUI;   // graphical user interface
    bool m_closed;      // did user close the interface?
};