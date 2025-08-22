#pragma once

#include "Entity.h"
#include "wzlibcpp/Property.hpp"
#include "World.h"

class Obj : public Entity
{
public:
    Obj(wz::Node *node,int id,int layer, World *world);
    ~Obj();
};
