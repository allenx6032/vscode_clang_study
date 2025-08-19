#include "Animation.h"

#include "Resources.h"

const auto AnimationTime = sf::seconds(0.15f);

Animation::Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite)
    : m_data(data), m_dir(dir), m_sprite(sprite)
{
    m_sprite.setTexture(Resources::instance().texture());
    update();
}

void Animation::direction(Direction dir)
{
    if (m_dir == dir)
    {
        m_ended = false;
        return;
    }

    m_dir = dir;
    m_ended = false;
}

bool Animation::update(sf::Time delta)
{
    m_elapsed += delta;

    if (m_elapsed >= AnimationTime && !m_ended)
    {
        m_elapsed -= AnimationTime;
        ++m_index;
        m_index %= m_data.m_data.find(m_dir)->second.size();
        update();

        // check if last frame
        if (m_index == m_data.m_data.find(m_dir)->second.size() -1)
        {
            m_ended = true;
            return false;    // animation ended
        }   
    } 
    return true;             // animation still going on
}

void Animation::resetAnimation()
{
    m_index = -1;
    m_ended = false;
}


void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data.find(m_dir)->second[m_index]);
}
