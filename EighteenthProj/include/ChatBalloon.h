#pragma once

#include "Entity.h"
#include "wzlibcpp/Property.hpp"
#include "World.h"
#include "Sprite.h"

class ChatBalloon : public Entity
{
public:
    ChatBalloon(int width, int height, const std::u16string &val);
    ~ChatBalloon();
    int get_width();
    int get_height();

public:
    Sprite *spr;
};
