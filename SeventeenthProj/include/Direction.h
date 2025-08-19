#pragma once

#include <SFML/SFML_Graphics.hpp>

enum class Direction
{
    Left,
    Right,
    Stay,
    Max,
    Up,
    Ladder,
    LadderUp,
    LadderDown,
    Rope,
    RopeUp,
    RopeDown,
    Dead,
    Hit,
    Jump,
    JumpRight,
    JumpLeft,
    ProneStab,
    Prone,
    Attack1,
    Attack2,
    Down,
    QuestPending,
    QuestComplete,
    None,
};

Direction opposite(Direction dir);
sf::Vector2f toVector(Direction dir);
