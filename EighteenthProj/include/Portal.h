#pragma once

#include "Entity.h"
#include "wzlibcpp/Property.hpp"
#include "World.h"
#include "AnimatedSprite.h"

class Portal : public Entity
{
public:
    Portal(wz::Node *node, World *world);
    ~Portal();

    std::unordered_map<std::u16string, AnimatedSprite *> aspr_map;
    int tm = 0;
    int pt = 0;
    std::u16string pn;
    std::u16string tn;
};
