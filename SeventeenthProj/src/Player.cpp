#include "Player.h"
#include "Ground.h"
#include "Wall.h"
#include "Ladder.h"
#include "Rope.h"
#include "Info.h"
#include "ReviveGUI.h"

constexpr auto AttackSpeed = 0.9f;
constexpr auto JumpSpeed = 0.5f;
constexpr auto HitDuration = 0.7f;
constexpr auto LevelUpAnimationTime = 3.f;

Direction Player::keyToDirection()
{
    static const
        std::initializer_list<std::pair<sf::Keyboard::Key, Direction>>
        keyToDirectionMapping =
    {
        { sf::Keyboard::Right, Direction::Right },
        { sf::Keyboard::Left,  Direction::Left },
        { sf::Keyboard::Up,    Direction::Stay },
        { sf::Keyboard::Down,  Direction::Prone},
        { sf::Keyboard::LControl,  Direction::Attack1 },
        { sf::Keyboard::LAlt,  Direction::Jump },
    };

    for (const auto& pair : keyToDirectionMapping)
    {
        if (sf::Keyboard::isKeyPressed(pair.first))
        {
            m_prone = false;
            switch (pair.first)
            {
            case sf::Keyboard::Left: return left();
            case sf::Keyboard::Right: return right();
            case sf::Keyboard::Up: return up();
            case sf::Keyboard::Down: return prone();
            case sf::Keyboard::LControl: return attack();
            case sf::Keyboard::LAlt: return jump();
            } 
            return pair.second;
        }
    }
    if (m_climbLadder)
        return Direction::Ladder;
    if (m_climbRope)
        return Direction::Rope;
    if (m_jump)
        return m_dir;
    return data.wasHit ? Direction::Hit : Direction::Stay;
}

Direction Player::attack()
{
    // cannot attack while climbing
    if (m_climbLadder || m_climbRope)
        return m_dir;

    m_attack = true;
    m_attackTime.restart();
    m_animation.resetAnimation();
    m_attackSound.play();

    if (m_prone)
    {
        return Direction::ProneStab;
    }

    int attackType = rand() % 2;
    if (attackType == 0)
    {
        return Direction::Attack1;
    }
    return Direction::Attack2;
}

Direction Player::jump()
{
    if (m_jump)
        return m_dir;

    if (m_hitTime.getElapsedTime().asSeconds() <= HitDuration)
        return m_dir;

    m_jumpSound.play();

    // jump left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_climbLadder = m_climbRope = false;
        m_sp.setScale(-1.f, 1.f);
        physics.velocity = sf::Vector2f(0, -9);
        updatePhysics();
        m_jump = true;
        m_jumpCooldown.restart();
        return Direction::JumpLeft;
    }    
    // jump right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_climbLadder = m_climbRope = false;
        m_sp.setScale(1.f, 1.f);
        physics.velocity = sf::Vector2f(0, -9);
        updatePhysics();
        m_jump = true;
        m_jumpCooldown.restart();
        return Direction::JumpRight;
    }
    // jump down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !m_climbLadder && !m_climbRope)
    {
        m_sp.move(0.f, 20.f);
        physics.velocity = physics.velocity = sf::Vector2f(0.f, -1.f);
        updatePhysics();
        m_jump = true;
        m_jumpCooldown.restart();
        return Direction::Jump;
    }
    // jump
    if (!m_climbLadder && !m_climbRope)
    {
        physics.velocity = sf::Vector2f(0, -9);
        updatePhysics();
        m_jump = true;
        m_jumpCooldown.restart();
        return Direction::Jump;
    }
    return m_dir;
}

Direction Player::left()
{
    if (m_jump)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            return attack();
        else
            return m_dir;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
        return jump();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return up();

    // cannot move while climbing
    if (m_climbLadder)
        return Direction::Ladder;
    if (m_climbRope)
        return Direction::Rope;

    // change player's direction to the left
    m_sp.setScale(-1.f, 1.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        return attack();
    return Direction::Left;
}

Direction Player::right()
{
    if (m_jump)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            return attack();
        else
            return m_dir;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
        return jump();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return up();

    // cannot move while climbing
    if (m_climbLadder)
        return Direction::Ladder;
    if (m_climbRope)
        return Direction::Rope;

    // change player's direction to the right
    m_sp.setScale(1.f, 1.f);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        return attack();
    return Direction::Right;
}

Direction Player::up()
{
    if (m_climbLadder)
        return Direction::LadderUp;
    if (m_climbRope)
        return Direction::RopeUp;
    if (m_jump)
        return m_dir;

    return Direction::Stay;
}

Direction Player::prone()
{
    if (m_jump)
        return m_dir;

    if (m_climbLadder)
        return Direction::LadderDown;

    if (m_climbRope)
        return Direction::RopeDown;

    m_prone = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
        return jump();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        return attack();

    return Direction::Prone;
}

bool Player::isAttacking()
{
    return m_attackTime.getElapsedTime().asSeconds() < AttackSpeed + 0.05;
}

bool Player::isJumping()
{
    return m_jump;
}
    
void Player::attackHitbox()
{
    auto hitbox = sf::RectangleShape(sf::Vector2f(40.f , m_sp.getGlobalBounds().height));
    
    // hitbox location based on where player is looking (we multiply by getScale)
    const auto offset = sf::Vector2f(45.f, 0.f) * m_sp.getScale().x;

    // hitbox location
    hitbox.setPosition(m_sp.getPosition().x - 20.f + offset.x, m_sp.getPosition().y);

    // check collision with movables
    for (auto& monster : Map::instance().monsters())
    {
        if (hitbox.getGlobalBounds().intersects(monster->getGlobalBounds()) &&
            monster->getData().HP != 0)
        {
            auto damage = randomDamage();

            // send amount of damage and direction of attack
            monster->wasHit(damage, m_sp.getScale());
            monster->playHitSound();
            Info::instance().showDamage("Player", damage, monster->getPosition());

            // check if the thing died and give rewards
            if (monster->isDead())
            {
                data.EXP += monster->getData().expReward;

                while (data.EXP >= data.MaxEXP)
                    levelUp();
            }
        }
    }
}

void Player::levelUp()
{
    m_levelUpSound.play();
    m_levelingUp = true;
    m_levelUpAnimation.resetAnimation();
    data.EXP -= data.MaxEXP;
    data.MaxEXP *= 1.5f;
    data.level += 1;
    data.MaxHP += 12;
    data.HP = data.MaxHP;
    data.damage += 1 + data.level * 0.2f;
}

Player::Player(const sf::Vector2f& position)
    : movingObject(position, Resources::Player, Resources::Death_Sound),
      m_attack(false), m_prone(false), m_climbLadder(false), m_climbRope(false), 
      m_levelingUp(false),
      m_levelUpAnimation(Resources::instance().animationData(Resources::LevelUp), Direction::Stay, m_effect),
      m_tombstoneAnimation(Resources::instance().animationData(Resources::Tombstone), Direction::Stay, m_effect),
      m_levelUpSound(Resources::instance().sound(Resources::LevelUp_Sound)),
      m_jumpSound(Resources::instance().sound(Resources::Jump_Sound)),
      m_attackSound(Resources::instance().sound(Resources::Sword_Sound))
{
    m_sp.setOrigin(sf::Vector2f(getGlobalBounds().width / 2.f, getGlobalBounds().height / 2.f));
    m_sp.setPosition(position);
}

void Player::update(sf::Time delta)
{
    if (data.HP == 0)
        return death(delta);

    // can't move during attack/jump
    if (!m_attack && !data.dead)
    {
        m_dir = keyToDirection();   // check for key input
        m_animation.direction(m_dir);
    }

    // remove hit status after hit duration
    if (m_hitTime.getElapsedTime().asSeconds() >= HitDuration)
        data.wasHit = false;

    // level up animation
    if (m_levelingUp)
    {
        m_levelingUp = m_levelUpAnimation.update(delta);
        m_effect.setPosition(m_sp.getPosition() - sf::Vector2f(150.f, 300.f));
    }
    else
        m_effect.setPosition(10000.f, 10000.f);

    if (m_attack)
    {
        // attack hitbox detection
        if (m_attackTime.getElapsedTime().asSeconds() >= AttackSpeed * 0.4f &&
            m_attackTime.getElapsedTime().asSeconds() <= AttackSpeed * 0.42f)
            attackHitbox();
        m_attack = m_animation.update(delta);
        return;
    }

    // animate & move player
    m_animation.update(delta);
    m_sp.move(toVector(m_dir) * delta.asSeconds() * data.Speed);
}

void Player::setSpawn(const sf::Vector2f& location)
{
    m_spawnLocation = location;
    setPosition(location);
}

void Player::death(sf::Time delta)
{
    if (!data.dead)
    {
        Info::instance().addGUI(Info::Revive);
        physics.drag = 0.9;
        data.dead = true;
        m_dir = Direction::Dead;
        m_animation.direction(m_dir);
        m_deathSound.play();
        m_tombstoneAnimation.resetAnimation();
        m_effect.setPosition(m_sp.getPosition() - sf::Vector2f(45.f, 175.f));
        data.EXP -= data.MaxEXP * 0.2;  // lose 20% exp on death
        if (data.EXP < 0.f)
            data.EXP = 0;
    }

    m_tombstoneAnimation.update(delta);
    auto animation = m_animation.update(delta);

    if (!animation)
        m_animation.resetAnimation();
}

sf::Vector2f Player::getPosition() const
{
    return sf::Vector2f();
}

void Player::handleCollision(gameObject& gameObject)
{
    // ignore self collision
    if (&gameObject == this) return;

    // use double dispatch to find which object
    gameObject.handleCollision(*this);
}

void Player::handleCollision(Monster& monster)
{

}

void Player::handleCollision(Ground& ground)
{
    if (m_sp.getPosition().y < ground.getPosition().y - 10.f &&
        physics.velocity.y > -0.41f)
    {
        m_climbLadder = m_climbRope = false;
        physics.velocity = sf::Vector2f(0.f, 0.1f);
        m_sp.move(0.f, -0.6f);

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            m_jump = false;

        // avoid stuck animations while holding down button
        if (m_jump)
        {
            m_dir = Direction::Prone;
            m_animation.direction(m_dir);
        }
    }
}

void Player::handleCollision(Wall& wall)
{
    if (m_sp.getPosition().x < wall.getPosition().x)
        m_sp.move(-0.8f, 0.f);
    else
        m_sp.move(0.8f, 0.f);
}

void Player::handleCollision(Ladder& ladder)
{
    // check if player is close
    if (m_sp.getPosition().x < ladder.getPosition().x - 10.f ||
        m_sp.getPosition().x > ladder.getPosition().x + 10.f)
        return;

    // climb up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
        m_sp.getPosition().y > ladder.getPosition().y + 5.f)
    {
        if (!m_climbLadder)
        {
            m_climbLadder = true;
            m_jump = false;
            m_attack = false;
            m_sp.setPosition(ladder.getPosition().x, m_sp.getPosition().y - 5.f);
        }
        physics.velocity = sf::Vector2f(0.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (!m_climbLadder)
        {
            m_climbLadder = true;
            m_jump = false;
            m_attack = false;
            m_sp.setPosition(ladder.getPosition().x, m_sp.getPosition().y + 5.f);
            m_dir = Direction::Ladder;
            m_animation.direction(m_dir);
        }
        physics.velocity = sf::Vector2f(0.f, -0.4f);
    }
    else if (m_climbLadder)
        physics.velocity = sf::Vector2f(0.f, -0.8f);
}

void Player::handleCollision(Rope& rope)
{
    // check if player is close
    if (m_sp.getPosition().x < rope.getPosition().x - 10.f ||
        m_sp.getPosition().x > rope.getPosition().x + 10.f)
        return;

    // climb up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
        m_sp.getPosition().y > rope.getPosition().y + 5.f)
    {
        if (!m_climbRope)
        {
            m_climbRope = true;
            m_jump = false;
            m_attack = false;
            m_sp.setPosition(rope.getPosition().x, m_sp.getPosition().y - 5.f);
        }
        physics.velocity = sf::Vector2f(0.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (!m_climbRope)
        {
            m_climbRope = true;
            m_jump = false;
            m_attack = false;
            m_sp.setPosition(rope.getPosition().x, m_sp.getPosition().y + 5.f);
        }
        physics.velocity = sf::Vector2f(0.f, -0.4f);
    }
    else if (m_climbRope)
        physics.velocity = sf::Vector2f(0.f, -0.8f);
}
