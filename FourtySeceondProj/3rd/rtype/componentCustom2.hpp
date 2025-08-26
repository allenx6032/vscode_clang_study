/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Component custom
*/

#pragma once
#include "gameEngine.hpp"
#include <iostream>

namespace component {
    // tag for the player
    struct Player {
    };

    // tag for the border
    struct Border {
    };

    // tag for the ball
    struct Ball {
    };

    // tag for the score
    struct Score {
        int _nb = 0;
    };

    struct Text {
        gameEngine::Text _text;
    };
}