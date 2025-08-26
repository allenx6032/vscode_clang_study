/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** System custom
*/

#include "systemCustom.hpp"

void gravitySystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::Velocity> &velocity,
                    SparseArray<component::Mass> &masses,
                    SparseArray<component::Unmovable> &unmovable)
{
    for (auto const &entity : transform) {
        if (!masses.has(entity.first) || !velocity.has(entity.first) || !transform.has(entity.first))
            continue;
        if (unmovable.has(entity.first))
            continue;
        auto &mass = masses[entity.first];
        auto &vel = velocity[entity.first];
        auto &tra = transform[entity.first];

        // gravity force between all entities
        for (auto const &other : transform) {
            if (!masses.has(other.first) || !velocity.has(other.first) || !transform.has(other.first))
                continue;
            if (other.first == entity.first)
                continue;
            auto const &otherTra = transform[other.first];
            auto &otherMass = masses[other.first];

            float distance = sqrt(pow(otherTra._posx - tra._posx, 2) + pow(otherTra._posy - tra._posy, 2));
            float force = (mass._mass * otherMass._mass) / pow(distance, 2);
            float angle = atan2(otherTra._posy - tra._posy, otherTra._posx - tra._posx);

            vel._velx += force * cos(angle);
            vel._vely += force * sin(angle);
        }
    }
}

void calcParallaxSystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::Paralax> &paralax)
{
    for (auto const &entity : transform) {
        if (!paralax.has(entity.first) || !transform.has(entity.first))
            continue;
        auto &par = paralax[entity.first];
        auto &tra = transform[entity.first];

        if (tra._posx < -par._paralax + 1)
            tra._posx += par._paralax * 2;
    }
}

void outlineBox2DDrawSystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::OutlineBox2D> &outlineBox2D,
                    SparseArray<component::Drawable> &drawable,
                    gameEngine::RenderWindow &window)
{
    for (auto const &entity : transform) {
        if (!outlineBox2D.has(entity.first) || !transform.has(entity.first) || !drawable.has(entity.first))
            continue;
        auto &tra = transform[entity.first];
        auto &out = outlineBox2D[entity.first];
        auto &draw = drawable[entity.first];

        if (!draw._isDrawable)
            continue;

        out._outline.setPosition(tra._posx, tra._posy);
        window.draw(out._outline);
    }
}

void colisionSystemCustom(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::ColisionBoxCustom> &colisionBox,
                    SparseArray<component::Velocity> &velocity,
                    SparseArray<component::Unmovable> &unmovable)
{
    for (auto const &entity : transform) {
        if (!colisionBox.has(entity.first) || !transform.has(entity.first))
            continue;
        auto const &col = colisionBox[entity.first];
        auto &tra = transform[entity.first];

        if (col._layer == component::ColisionBoxCustom::Layer::PLAYER) {
            // prevent entity from going out of the window
            if (tra._posx + (velocity[entity.first]._velx * ge.deltaTime) < 0 || tra._posx + (velocity[entity.first]._velx * ge.deltaTime) > WINDOW_WIDTH) {
                tra._posx -= velocity[entity.first]._velx * ge.deltaTime;
                velocity[entity.first]._velx = 0;
            }

            if (tra._posy + (velocity[entity.first]._vely * ge.deltaTime) < 0 || tra._posy + (velocity[entity.first]._vely * ge.deltaTime) > WINDOW_HEIGHT) {
                tra._posy -= velocity[entity.first]._vely * ge.deltaTime;
                velocity[entity.first]._vely = 0;
            }
        }

        // check collision with all other entities with a colisionBox and replace the entity if needed
        for (auto const &other : colisionBox) {
            if (other.first == entity.first)
                continue;
            auto const &otherCol = colisionBox[other.first];
            auto &otherTra = transform[other.first];

            // the colision box use the tra pos + its offset as the center of the box
            // the width and height are the size of the box and is affected by the scale

            if (!col._layersMatrix[col._layer][otherCol._layer])
                continue;

            float x1 = tra._posx + col._offsetx;
            float y1 = tra._posy + col._offsety;
            float x2 = otherTra._posx + otherCol._offsetx;
            float y2 = otherTra._posy + otherCol._offsety;

            float w1 = col._width;
            float h1 = col._height;
            float w2 = otherCol._width;
            float h2 = otherCol._height;

            // std::cout << "-------------------------------" << std::endl;

            // std::cout << "x1: " << x1 << std::endl;
            // std::cout << "x2: " << x2 << std::endl;

            // std::cout << "y1: " << y1 << std::endl;
            // std::cout << "y2: " << y2 << std::endl;

            // std::cout << "w1: " << w1 << std::endl;
            // std::cout << "w2: " << w2 << std::endl;

            // std::cout << "h1: " << h1 << std::endl;
            // std::cout << "h2: " << h2 << std::endl;

            if ((x1 < x2 + w2 && x1 + w1 > x2 &&
                y1 < y2 + h2 && y1 + h1 > y2) ||
                (x2 < x1 + w1 && x2 + w2 > x1 &&
                y2 < y1 + h1 && y2 + h2 > y1)) {
                // std::cout << "colision detected" << std::endl;
                if (col._isTrigger || otherCol._isTrigger)
                    continue;
                if (unmovable.has(entity.first)) {
                    otherTra._posx -= velocity[other.first]._velx * ge.deltaTime;
                    otherTra._posy -= velocity[other.first]._vely * ge.deltaTime;
                } else if (unmovable.has(other.first)) {
                    tra._posx -= velocity[entity.first]._velx * ge.deltaTime;
                    tra._posy -= velocity[entity.first]._vely * ge.deltaTime;
                } else {
                    tra._posx -= velocity[entity.first]._velx * ge.deltaTime;
                    tra._posy -= velocity[entity.first]._vely * ge.deltaTime;
                    velocity[entity.first]._velx = -velocity[entity.first]._velx;
                    velocity[entity.first]._vely = -velocity[entity.first]._vely;
                }
            }
        }
    }
}

void enemyPattern(GameEngine &ge,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::Velocity> &velocity,
                        SparseArray<component::EnemyType> &type,
                        SparseArray<component::hasTouch> &hasTouch,
                        SparseArray<component::IsEnemy> &isEnemy
)
{
    for (auto &enemy : isEnemy) {
        if (!transform.has(enemy.first) || !type.has(enemy.first))
            continue;
        auto &tra = transform[enemy.first];
        auto &vel = velocity[enemy.first];
        auto &enemyType = type[enemy.first];
        auto &touch = hasTouch[enemy.first];

        if (enemyType._type == component::EnemyType::Type::SIMPLE) {
            vel._vely = computeEnemySimplePattern(ge, tra._posx) * 60;
            if (tra._posy + (vel._vely * ge.deltaTime) < 0 || tra._posy + (vel._vely * ge.deltaTime) > 1080)
                vel._vely = -vel._vely;
            tra._posy += vel._vely * ge.deltaTime;
        } else if (enemyType._type == component::EnemyType::Type::MECHA) {
            tra._posx += vel._velx * ge.deltaTime;
        } else if (enemyType._type == component::EnemyType::Type::BOSS) {
            if (tra._posx < 1920 - 142 * 1.5)
                vel._velx = 0;
        } else if (enemyType._type == component::EnemyType::Type::OTHER) {
            if (tra._posy + (vel._vely * ge.deltaTime) < 0 || tra._posy + (vel._vely * ge.deltaTime) > 1080)
                touch._hasTouch = true;
            if (touch._hasTouch && tra._posy + (vel._vely * ge.deltaTime) > 1080) {
                vel._vely = -240.0f;
                touch._hasTouch = false;
            } else if (touch._hasTouch && tra._posy + (vel._vely * ge.deltaTime) < 0) {
                vel._vely = 240.0f;
                touch._hasTouch = false;
            }
            tra._posy += vel._vely * ge.deltaTime;
        } else if (enemyType._type == component::EnemyType::Type::MISSILE) {
            if (tra._posy + (vel._vely * ge.deltaTime) < 0 || tra._posy + (vel._vely * ge.deltaTime) > 1080)
                touch._hasTouch = true;
            if (touch._hasTouch && tra._posy + (vel._vely * ge.deltaTime) > 1080) {
                vel._vely = -300.0f;
                touch._hasTouch = false;
            } else if (touch._hasTouch && tra._posy + (vel._vely * ge.deltaTime) < 0) {
                vel._vely = 300.0f;
                touch._hasTouch = false;
            }
            tra._posy += vel._vely * ge.deltaTime;
        }
    }
}
