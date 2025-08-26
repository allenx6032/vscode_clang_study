/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Server system custom
*/

#pragma once
#include "rtype/gameEngine.hpp"
#include "rtype/componentCustom.hpp"
#include "rtype/api.hpp"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void takeHitSystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::ColisionBoxCustom> &colisionBox,
                    SparseArray<component::Bullet> &bullets,
                    SparseArray<component::Health> &health,
                    int &enemySpawnNumber);
void deleteOutOfMapBullets(GameEngine &ge,
                            SparseArray<component::Transform> &transform,
                            SparseArray<component::Bullet> &bullets);
void enemyHitPlayerSystem(GameEngine &ge,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::ColisionBoxCustom> &colisionBox);
