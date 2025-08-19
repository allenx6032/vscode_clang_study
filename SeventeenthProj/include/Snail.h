#pragma once

#include "Monster.h"

#include <SFML/SFML_Graphics.hpp>

class Snail : public Monster
{
public:
    Snail(const sf::Vector2f& position)
        : Monster(position, Resources::Snail, Resources::SnailHit_Sound, Resources::SnailDeath_Sound)
    {
        m_sp.setOrigin(sf::Vector2f(getGlobalBounds().width / 1.8f, getGlobalBounds().height / 2.f));
        data.name = "Snail";
        data.expReward = 9;
        data.level = 1;
        data.damage = 3;
        data.HP = 8;
        data.MaxHP = data.HP;
        data.Speed = 80.f;
        m_info.setName(data.name);
        m_info.setLevel(data.level);
    }
};
