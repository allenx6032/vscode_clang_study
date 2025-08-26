/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Server system custom
*/

#pragma once
#include "rtype/gameEngine.hpp"
#include "rtype/systemCustom.hpp"
#include "rtype/systemCustom2.hpp"

void ballColisionSystemServer(GameEngine &ge,
                        SparseArray<component::Ball> &ball,
                        SparseArray<component::Border> &border,
                        SparseArray<component::Player> &player,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::ColisionBox> &colisionBox,
                        int &scorePlayer1, int &scorePlayer2);
