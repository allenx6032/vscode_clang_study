#pragma once

#include "Direction.h"
#include "AnimationData.h"

#include <SFML/SFML_Graphics.hpp>

class Animation
{
public:
    Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite);

    // Set the direction; the sprite will take the relevant texture rect
    void direction(Direction dir);

    // Add more time to the elapsed time; if enough time passed, it
    // updates the sprite to show the next frame in the animation
    bool update(sf::Time delta);

    // resets index
    void resetAnimation();

private:
    // Update the sprite to take the correct part of the texture,
    // based on current dir and index
    void update();

    const AnimationData& m_data;
    sf::Time m_elapsed = {};
    Direction m_dir = Direction::Stay;
    int m_index = 0;
    sf::Sprite& m_sprite;
    bool m_ended = false;
};
