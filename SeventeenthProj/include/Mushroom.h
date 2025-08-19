#pragma once

#include "Monster.h"

#include <SFML/SFML_Graphics.hpp>

class Mushroom : public Monster
{
public:
    using movingObject::handleCollision;

    Mushroom(const sf::Vector2f& position)
        : Monster(position, Resources::Mushroom, Resources::HitSound1, Resources::MushroomDeath_Sound)
    {
        m_sp.setOrigin(sf::Vector2f(getGlobalBounds().width / 1.8f, getGlobalBounds().height / 2.f));
        data.name = "Mushroom";
        data.expReward = 45;
        data.level = 8;
        data.damage = 20;
        data.HP = 80;
        data.MaxHP = data.HP;
        data.Speed = 140.f;
        m_info.setName(data.name);
        m_info.setLevel(data.level);
    }
};
