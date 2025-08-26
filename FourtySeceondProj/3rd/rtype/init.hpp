/*
** EPITECH PROJECT, 2023
** init.hpp
** File description:
** init.hpp
*/

#pragma once

#include "gameEngine.hpp"
#include "componentCustom.hpp"

void setUpComponents(GameEngine &ge);
size_t getFromIdComponent(GameEngine &ge, size_t id);
bool hasIdComponent(GameEngine &ge, size_t id);
void initLobbyScreen(GameEngine &ge);
Entity newLobby(GameEngine &ge, float posx, float posy, size_t lobbyId);
Entity initButton(GameEngine &ge, std::string path, float posx, float posy, float scalex, float scaley);

