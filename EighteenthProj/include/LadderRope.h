#pragma once
#include "Entity.h"
#include "wzlibcpp/Property.hpp"
#include "World.h"

class LadderRope : public Entity
{
public:
    LadderRope(wz::Node *node, World *world);
    ~LadderRope();

public:
    // lr的附加属性
    int l;
    int uf;
    int page;
};