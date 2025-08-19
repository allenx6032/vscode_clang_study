#pragma once

#include "Monster.h"

#include <SFML/SFML_Graphics.hpp>

class Shroom : public Monster
{
public:
    Shroom(const sf::Vector2f& position)
        : Monster(position, Resources::Shroom, Resources::HitSound1, Resources::ShroomDeath_Sound)
    {
        m_sp.setOrigin(sf::Vector2f(getGlobalBounds().width / 1.8f, getGlobalBounds().height / 2.f));
        data.name = "Shroom";
        data.expReward = 15;
        data.level = 3;
        data.damage = 5;
        data.HP = 20;
        data.MaxHP = data.HP;
        data.Speed = 100.f;
        m_info.setName(data.name);
        m_info.setLevel(data.level);
    }
};
