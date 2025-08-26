/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** System custom
*/

#pragma once
#include "gameEngine.hpp"
#include "api.hpp"
#include "componentCustom.hpp"


#define COLLISION_MATRIX { \
    /*player, missile, enemy, obstacle */ \
        {true, false, true, true},  /* player */\
        {false, false, true, true}, /* missile */\
        {true, true, false, true},   /* enemy */\
        {true, true, true, false}   /* obstacle */\
}

void gravitySystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::Velocity> &velocity,
                    SparseArray<component::Mass> &masses,
                    SparseArray<component::Unmovable> &unmovable);
void calcParallaxSystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::Paralax> &paralax);
void outlineBox2DDrawSystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::OutlineBox2D> &outlineBox2D,
                    SparseArray<component::Drawable> &drawable,
                    gameEngine::RenderWindow &window);
void colisionSystemCustom(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::ColisionBoxCustom> &colisionBox,
                    SparseArray<component::Velocity> &velocity,
                    SparseArray<component::Unmovable> &unmovable);

void enemyPattern(GameEngine &ge,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::Velocity> &velocity,
                        SparseArray<component::EnemyType> &type,
                        SparseArray<component::hasTouch> &asTouch,
                        SparseArray<component::IsEnemy> &isEnemy);
