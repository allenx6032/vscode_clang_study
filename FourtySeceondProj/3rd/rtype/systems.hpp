/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "gameEngine.hpp"
#include <cmath>

void transformLog(GameEngine &ge,
                SparseArray<component::Transform> const &transform);
void velocityLog(GameEngine &ge,
                SparseArray<component::Velocity> const &velocity);
void updatePosSystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::Velocity> &velocity);
void loadSpriteTexture(GameEngine &ge,
                    SparseArray<component::Sprite> &sprite,
                    SparseArray<component::Texture> &texture);
void drawSprite(GameEngine &ge,
                SparseArray<component::Sprite> &sprite,
                SparseArray<component::Drawable> &drawable,
                gameEngine::RenderWindow &window);
void refreshSpriteSystem(GameEngine &ge,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::Sprite> &sprite);
void colisionSystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::ColisionBox> &colisionBox,
                    SparseArray<component::Velocity> &velocity,
                    SparseArray<component::Unmovable> &unmovable);
void garbageCollectorSystem(GameEngine &ge,
                            SparseArray<component::ToDelete> &toDelete);
void animationSystem(GameEngine &ge,
                    SparseArray<component::Animation> &animation,
                    SparseArray<component::Sprite> &sprite);
