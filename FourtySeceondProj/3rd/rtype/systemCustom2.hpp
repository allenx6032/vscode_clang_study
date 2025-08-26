/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** System custom
*/

#pragma once
#include "gameEngine.hpp"
#include "componentCustom2.hpp"

#define M_PI 3.14159265358979323846
#define RAD_TO_DEG 180 / M_PI
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void playerColisionSystem(GameEngine &ge,
                        SparseArray<component::Player> &player,
                        SparseArray<component::Border> &border,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::ColisionBox> &colisionBox);

void ballColisionSystem(GameEngine &ge,
                        SparseArray<component::Ball> &ball,
                        SparseArray<component::Border> &border,
                        SparseArray<component::Player> &player,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::ColisionBox> &colisionBox,
                        gameEngine::Sound &sound);

void refreshScoreSystem(GameEngine &ge,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::Score> &score,
                        SparseArray<component::Text> &text,
                        int &scorePlayer1, int &scorePlayer2);

void drawScoreSystem(GameEngine &ge,
                    SparseArray<component::Text> &text,
                    SparseArray<component::Score> &score,
                    SparseArray<component::Drawable> &drawable,
                    gameEngine::RenderWindow &window);
