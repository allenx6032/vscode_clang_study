/*
** EPITECH PROJECT, 2023
** gameClient
** File description:
** game
*/

#pragma once
#include "systemCustom.hpp"

Entity createBall(GameEngine &ge, bool isServer = false);
Entity createPlayerLeft(GameEngine &ge, bool isServer = false);
Entity createPlayerRight(GameEngine &ge, bool isServer = false);
std::vector<Entity> createBorder(GameEngine &ge, bool isServer = false);
std::vector<Entity> createScore(GameEngine &ge, gameEngine::Font &font);
void createDottedLine(GameEngine &ge);
