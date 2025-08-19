#pragma once

#include "Monster.h"

#include <SFML/SFML_Graphics.hpp>

class BlueSnail : public Monster
{
public:
    BlueSnail(const sf::Vector2f& position)
        : Monster(position, Resources::BlueSnail, Resources::SnailHit_Sound, Resources::SnailDeath_Sound)
    {
        m_sp.setOrigin(sf::Vector2f(getGlobalBounds().width / 1.8f, getGlobalBounds().height / 2.f));
        data.name = "Blue Snail";
        data.expReward = 12;
        data.level = 2;
        data.damage = 4;
        data.HP = 15;
        data.MaxHP = data.HP;
        data.Speed = 95.f;
        m_info.setName(data.name);
        m_info.setLevel(data.level);
    }
};
