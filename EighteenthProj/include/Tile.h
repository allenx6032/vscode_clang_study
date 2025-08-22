#pragma once

#include "Entity.h"
#include "wzlibcpp/Property.hpp"
#include "World.h"

class Tile : public Entity
{
public:
    Tile(wz::Node *node, const std::u16string &ts, int layer, int id, World *world);
    ~Tile();
};
