#include "Direction.h"

#include <stdexcept>

Direction opposite(Direction dir)
{
    switch (dir)
    {
    case Direction::Up:
        return Direction::Down;
    case Direction::Down:
        return Direction::Up;
    case Direction::Right:
        return Direction::Left;
    case Direction::Left:
        return Direction::Right;
    case Direction::JumpRight:
        return Direction::JumpLeft;
    case Direction::JumpLeft:
        return Direction::JumpRight;
    case Direction::Jump:
        return Direction::Jump;
    case Direction::Stay:
        return Direction::Stay;
    }
    throw std::runtime_error("Unknown direction");
}

sf::Vector2f toVector(Direction dir)
{
    switch (dir)
    {
    case Direction::Ladder:
        return { 0, 0 };
    case Direction::LadderUp:
        return { 0, -1 };
    case Direction::LadderDown:
        return { 0, 1 };
    case Direction::Rope:
        return { 0, 0 };
    case Direction::RopeUp:
        return { 0, -1 };
    case Direction::RopeDown:
        return { 0, 1 };
    case Direction::Up:
        return { 0, 0 };
    case Direction::Right:
        return { 1, 0 };
    case Direction::Left:
        return { -1, 0 };
    case Direction::Stay:
        return { 0, 0 };
    case Direction::Attack1:
        return { 0, 0 };
    case Direction::Attack2:
        return { 0, 0 };
    case Direction::Jump:
        return { 0, 0 };
    case Direction::JumpRight:
        return { 1, 0 };
    case Direction::JumpLeft:
        return { -1, 0 };
    case Direction::Prone:
        return { 0, 0 };
    case Direction::ProneStab:
        return { 0, 0 };
    case Direction::Hit:
        return { 0, 0 };
    case Direction::Dead:
        return { 0, 0 };
    }
    throw std::runtime_error("Unknown direction");
}
