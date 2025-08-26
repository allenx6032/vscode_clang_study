/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#include "systems.hpp"

void transformLog(GameEngine &ge,
                SparseArray<component::Transform> const &transform)
{
    for (auto const &entity : transform) {
        std::cout << "Entity " << entity.first << " has a transform component:" << std::endl;
        std::cout << entity.second << std::endl;
    }
}

void velocityLog(GameEngine &ge,
                SparseArray<component::Velocity> const &velocity)
{
    for (auto const &entity : velocity) {
        std::cout << "Entity " << entity.first << " has a velocity component:" << std::endl;
        std::cout << entity.second << std::endl;
    }
}

void updatePosSystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::Velocity> &velocity)
{
    for (auto const &entity : transform) {
        if (!velocity.has(entity.first) || !transform.has(entity.first))
            continue;
        auto const &vel = velocity[entity.first];
        auto &pos = transform[entity.first];

        // std::cout << "vel: " << vel.velx << ", " << vel.vely << std::endl;

        pos._posx += vel._velx * ge.deltaTime;
        pos._posy += vel._vely * ge.deltaTime;
    }
}

void refreshSpriteSystem(GameEngine &ge,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::Sprite> &sprite)
{
    for (auto const &entity : transform) {
        if (!sprite.has(entity.first) || !transform.has(entity.first))
            continue;
        auto const &tra = transform[entity.first];
        auto &spr = sprite[entity.first];

        // std::cout << "tra: " << tra.posx << ", " << tra.posy << std::endl;

        spr._sprite.setScale(tra._scalex, tra._scaley);
        spr._sprite.setRotation(tra._rotx);
        spr._sprite.setPosition(tra._posx, tra._posy);
    }
}

void loadSpriteTexture(GameEngine &ge,
                        SparseArray<component::Sprite> &sprite,
                        SparseArray<component::Texture> &texture)
{
    for (auto const &entity : sprite) {
        if (!texture.has(entity.first) || !sprite.has(entity.first))
            continue;
        auto const &tex = texture[entity.first];
        auto &spr = sprite[entity.first];

        spr._sprite.setTexture(tex._texture);
    }
}

void drawSprite(GameEngine &ge,
                SparseArray<component::Sprite> &sprite,
                SparseArray<component::Drawable> &drawable,
                gameEngine::RenderWindow &window)
{
    for (auto const &entity : sprite) {
        if (!drawable.has(entity.first) || !sprite.has(entity.first))
            continue;
        auto const &draw = drawable[entity.first];
        auto &spr = sprite[entity.first];

        if (draw._isDrawable == 1)
            window.draw(spr._sprite);
    }
}

void colisionSystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::ColisionBox> &colisionBox,
                    SparseArray<component::Velocity> &velocity,
                    SparseArray<component::Unmovable> &unmovable)
{
    for (auto const &entity : transform) {
        if (!colisionBox.has(entity.first) || !transform.has(entity.first))
            continue;
        auto const &col = colisionBox[entity.first];
        auto &tra = transform[entity.first];

        // check collision with all other entities with a colisionBox and replace the entity if needed
        for (auto const &other : colisionBox) {
            if (other.first == entity.first)
                continue;
            auto const &otherCol = colisionBox[other.first];
            auto &otherTra = transform[other.first];

            if (tra._posx + col._width > otherTra._posx && tra._posx < otherTra._posx + otherCol._width &&
                tra._posy + col._height > otherTra._posy && tra._posy < otherTra._posy + otherCol._height) {
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

void garbageCollectorSystem(GameEngine &ge,
                            SparseArray<component::ToDelete> &toDelete)
{
    while (toDelete.size() > 0) {
        for (auto const &entity : toDelete) {
            if (toDelete.has(entity.first)) {
                ge.ecsKillEntity(ge.ecsEntityFromIndex(entity.first));
                break;
            }
        }
    }
}

void animationSystem(GameEngine &ge,
                    SparseArray<component::Animation> &animation,
                    SparseArray<component::Sprite> &sprite)
{
    for (auto const &entity : animation) {
        if (!animation.has(entity.first) || !sprite.has(entity.first))
            continue;
        auto &anim = animation[entity.first];
        auto &spr = sprite[entity.first];

        if (anim._jsonPath == "")
            continue;

        if (anim._checked == false) {
            ge.jsonLoadFile(anim._jsonPath);
            anim._checked = true;

            auto &json = ge.jsonGetFile(anim._jsonPath);
            spr._rect.left = json["frames"][anim._currentFrame]["x"];
            spr._rect.top = json["frames"][anim._currentFrame]["y"];
            spr._rect.width = json["frames"][anim._currentFrame]["width"];
            spr._rect.height = json["frames"][anim._currentFrame]["height"];
            spr._sprite.setTextureRect(spr._rect);
        }

        if (anim._automaticAnimation == true) {
            if ((sf::Time)anim._clock.getElapsedTime() > (sf::Time)anim._time) {
                anim._clock.restart();
                auto &json = ge.jsonGetFile(anim._jsonPath);
                if (anim._currentFrame >= json["frames"].size()) {
                    if (anim._isLooping == true)
                        anim._currentFrame = 0;
                    else
                        anim._currentFrame = json["frames"].size() - 1;
                }
                spr._rect.left = json["frames"][anim._currentFrame]["x"];
                spr._rect.top = json["frames"][anim._currentFrame]["y"];
                spr._rect.width = json["frames"][anim._currentFrame]["width"];
                spr._rect.height = json["frames"][anim._currentFrame]["height"];
                spr._sprite.setTextureRect(spr._rect);
                anim._currentFrame++;
            }
        } else {
            auto &json = ge.jsonGetFile(anim._jsonPath);
            if (anim._currentFrame >= json["frames"].size())
                    anim._currentFrame = json["frames"].size() - 1;
            if (anim._currentFrame < 0)
                    anim._currentFrame = 0;
            spr._rect.left = json["frames"][anim._currentFrame]["x"];
            spr._rect.top = json["frames"][anim._currentFrame]["y"];
            spr._rect.width = json["frames"][anim._currentFrame]["width"];
            spr._rect.height = json["frames"][anim._currentFrame]["height"];
            spr._sprite.setTextureRect(spr._rect);
        }

    }
}
