#pragma once

#include "movingObject.h"
#include "MonsterInfo.h"

class Monster : public movingObject
{
public:
    using movingObject::handleCollision;

    Monster(const sf::Vector2f& position, const Resources::Objects& object,
            const int& hitSound, const int& deathSound);

    void update(sf::Time delta) override;
    void death(sf::Time delta);
    void playHitSound();
    void drawInfo(sf::RenderWindow& window);

    // Collision Handlers
    void handleCollision(gameObject& gameObject);
    void handleCollision(Player& player) override;
    void handleCollision(Monster& monster) {}; // ignore another monster
    void handleCollision(Ground& ground) override;
    void handleCollision(Wall& wall) override;
    void handleCollision(MonsterWall& monsterWall) override;
    void handleCollision(Ladder& ladder) {};
    void handleCollision(Portal& portal) {};
    virtual void handleCollision(Rope& rope) {};

protected:
    sf::Clock m_aiTime;
    sf::Sound m_hitSound;
    MonsterInfo m_info;
};
