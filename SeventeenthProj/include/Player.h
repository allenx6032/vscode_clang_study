#pragma once

#include "movingObject.h"

class Player : public movingObject
{
public:
    using movingObject::handleCollision;

    Player(const sf::Vector2f& position);

    bool isAttacking();
    bool isJumping();
    void update(sf::Time delta) override;
    void setSpawn(const sf::Vector2f& location);
    void gameFinished();
    
    sf::Vector2f getPosition() const;   

    // Collision Handlers
    void handleCollision(gameObject& gameObject);
    void handleCollision(Player& player) override {};   // ignore another player
    void handleCollision(Monster& monster) override;
    void handleCollision(Ground& ground) override;
    void handleCollision(Wall& wall) override;
    void handleCollision(MonsterWall& monsterWall) override {};    // ignore
    virtual void handleCollision(Ladder& ladder);
    virtual void handleCollision(Portal& portal) {};
    virtual void handleCollision(Rope& rope);

private:
    Direction keyToDirection();
    Direction attack();
    Direction jump();
    Direction left();
    Direction right();
    Direction up();
    Direction prone();

    void death(sf::Time delta);
    void attackHitbox();
    void levelUp();

    bool m_attack;
    bool m_prone;
    bool m_climbLadder;
    bool m_climbRope;
    bool m_levelingUp;

    sf::Clock m_attackTime;
    sf::Clock m_animationTime;
    sf::Clock m_jumpCooldown;
    sf::Sound m_levelUpSound;
    sf::Sound m_jumpSound;
    sf::Sound m_attackSound;

    Animation m_levelUpAnimation;
    Animation m_tombstoneAnimation;
};