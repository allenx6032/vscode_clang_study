#pragma once

#include "Monster.h"

#include <SFML/SFML_Graphics.hpp>

class Stump : public Monster
{
public:
    Stump(const sf::Vector2f& position)
        : Monster(position, Resources::Stump, Resources::StumpHit_Sound, Resources::StumpDeath_Sound)
    {
        m_sp.setOrigin(sf::Vector2f(getGlobalBounds().width / 1.8f, getGlobalBounds().height / 2.f));
        data.name = "Stump";
        data.expReward = 24;
        data.level = 4;
        data.damage = 7;
        data.HP = 40;
        data.MaxHP = data.HP;
        data.Speed = 60.f;
        m_info.setName(data.name);
        m_info.setLevel(data.level);
    }
};
