#include "Resources.h"

#include "Direction.h"

#include <stdexcept>

namespace
{   
    AnimationData MushroomData()
    {
        const auto size = sf::Vector2i(65, 71);
        const auto initSpace = sf::Vector2i(116, 20);
        const auto middleSpace = sf::Vector2i(0, 14);

        auto Mushroom = AnimationData{};    
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += middleSpace;
            currentStart.y += size.y;
            return currentStart;
        };

        Mushroom.m_data[Direction::Dead].emplace_back(currentStart, size);
        Mushroom.m_data[Direction::Dead].emplace_back(nextStart(), size);
        Mushroom.m_data[Direction::Dead].emplace_back(nextStart(), size);
        Mushroom.m_data[Direction::Hit].emplace_back(nextStart(), size);
        Mushroom.m_data[Direction::Jump].emplace_back(nextStart(), size);
        Mushroom.m_data[Direction::Left].emplace_back(nextStart(), size);
        Mushroom.m_data[Direction::Right].emplace_back(currentStart, size);
        Mushroom.m_data[Direction::Left].emplace_back(nextStart(), size);
        Mushroom.m_data[Direction::Right].emplace_back(currentStart, size);
        Mushroom.m_data[Direction::Left].emplace_back(nextStart(), size);
        Mushroom.m_data[Direction::Right].emplace_back(currentStart, size);
        Mushroom.m_data[Direction::Stay].emplace_back(nextStart(), size);
        Mushroom.m_data[Direction::Stay].emplace_back(nextStart(), size);

        return Mushroom;
    }

    AnimationData playerData()
    {
        const auto walkSize = sf::Vector2i(61, 80);
        const auto deathSize = sf::Vector2i(81, 100);
        const auto size = sf::Vector2i(95, 80);
        const auto initSpace = sf::Vector2i(232, 2);
        const auto middleSpace = sf::Vector2i(0, 20);

        auto player = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += middleSpace;
            currentStart.y += size.y;
            return currentStart;
        };

        player.m_data[Direction::Ladder].emplace_back(currentStart, size);
        player.m_data[Direction::LadderUp].emplace_back(currentStart, size);
        player.m_data[Direction::LadderDown].emplace_back(currentStart, size);
        player.m_data[Direction::LadderUp].emplace_back(nextStart(), size);
        player.m_data[Direction::LadderDown].emplace_back(currentStart, size);
        player.m_data[Direction::Rope].emplace_back(nextStart(), size);
        player.m_data[Direction::RopeUp].emplace_back(currentStart, size);
        player.m_data[Direction::RopeDown].emplace_back(currentStart, size);
        player.m_data[Direction::RopeUp].emplace_back(nextStart(), size);
        player.m_data[Direction::RopeDown].emplace_back(currentStart, size);
        player.m_data[Direction::Hit].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Hit].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Hit].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Hit].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Jump].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::JumpLeft].emplace_back(currentStart, walkSize);
        player.m_data[Direction::JumpRight].emplace_back(currentStart, walkSize);
        player.m_data[Direction::Prone].emplace_back(nextStart(), size);
        player.m_data[Direction::ProneStab].emplace_back(nextStart(), size);
        player.m_data[Direction::ProneStab].emplace_back(nextStart(), size);
        player.m_data[Direction::ProneStab].emplace_back(currentStart, size);
        player.m_data[Direction::ProneStab].emplace_back(currentStart, size);
        player.m_data[Direction::ProneStab].emplace_back(currentStart, size);
        player.m_data[Direction::Attack1].emplace_back(nextStart(), size);
        player.m_data[Direction::Attack1].emplace_back(nextStart(), size);
        player.m_data[Direction::Attack1].emplace_back(nextStart(), size);
        player.m_data[Direction::Attack1].emplace_back(currentStart, size);
        player.m_data[Direction::Attack1].emplace_back(currentStart, size);
        player.m_data[Direction::Stay].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Stay].emplace_back(currentStart, walkSize);
        player.m_data[Direction::Stay].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Stay].emplace_back(currentStart, walkSize);
        player.m_data[Direction::Stay].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Stay].emplace_back(currentStart, walkSize);
        player.m_data[Direction::Stay].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Stay].emplace_back(currentStart, walkSize);
        player.m_data[Direction::Attack2].emplace_back(nextStart(), size);
        player.m_data[Direction::Attack2].emplace_back(nextStart(), size);
        player.m_data[Direction::Attack2].emplace_back(nextStart(), size);
        player.m_data[Direction::Attack2].emplace_back(currentStart, size);
        player.m_data[Direction::Attack2].emplace_back(currentStart, size);
        player.m_data[Direction::Left].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Right].emplace_back(currentStart, walkSize);
        player.m_data[Direction::Left].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Right].emplace_back(currentStart, walkSize);
        player.m_data[Direction::Left].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Right].emplace_back(currentStart, walkSize);
        player.m_data[Direction::Left].emplace_back(nextStart(), walkSize);
        player.m_data[Direction::Right].emplace_back(currentStart, walkSize);
        player.m_data[Direction::Dead].emplace_back(nextStart() + sf::Vector2i(-10, 0), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-12,0), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-14,0), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-16,-2), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-18,-4), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-18,-6), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-18,-8), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-16,-10), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-14,-12), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-12,-12), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-10,-12), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-8,-12), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-6,-12), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-4,-10), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-2,-8), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-2,-6), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-2,-4), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-4,-2), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-6, 0), deathSize);
        player.m_data[Direction::Dead].emplace_back(currentStart + sf::Vector2i(-8, 0), deathSize);

        return player;
    }
}

AnimationData PortalData()
{
    const auto size = sf::Vector2i(87, 262);
    const auto initSpace = sf::Vector2i(330, 0);
    const auto middleSpace = sf::Vector2i(0, 14);

    auto Portal = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    Portal.m_data[Direction::Stay].emplace_back(currentStart, size);
    Portal.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Portal.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Portal.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Portal.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Portal.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Portal.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Portal.m_data[Direction::Stay].emplace_back(nextStart(), size);

    return Portal;
}

AnimationData LevelUpData()
{
    const auto size = sf::Vector2i(296, 345);
    const auto initSpace = sf::Vector2i(433, 0);
    const auto middleSpace = sf::Vector2i(0, 0);

    auto LevelUp = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    LevelUp.m_data[Direction::Stay].emplace_back(currentStart, size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(nextStart(), size);
    LevelUp.m_data[Direction::Stay].emplace_back(currentStart, size);

    return LevelUp;
}

AnimationData TombstoneData()
{
    const auto size = sf::Vector2i(98, 213);
    const auto initSpace = sf::Vector2i(732, 0);
    const auto middleSpace = sf::Vector2i(0, 0);

    auto Tombstone = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    Tombstone.m_data[Direction::Stay].emplace_back(currentStart, size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Tombstone.m_data[Direction::Stay].emplace_back(nextStart(), size);

    return Tombstone;
}

AnimationData HeenaData()
{
    const auto size = sf::Vector2i(56, 55);
    const auto initSpace = sf::Vector2i(19, 20);
    const auto middleSpace = sf::Vector2i(0, 20);

    auto Heena = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Heena.m_data[Direction::Stay].emplace_back(currentStart, size);
    Heena.m_data[Direction::Stay].emplace_back(currentStart, size);
    Heena.m_data[Direction::Stay].emplace_back(currentStart, size);
    Heena.m_data[Direction::Stay].emplace_back(currentStart, size);
    Heena.m_data[Direction::Stay].emplace_back(currentStart, size);
    Heena.m_data[Direction::Stay].emplace_back(currentStart, size);
    Heena.m_data[Direction::Stay].emplace_back(currentStart, size);
    Heena.m_data[Direction::Stay].emplace_back(currentStart, size);
    Heena.m_data[Direction::Stay].emplace_back(currentStart, size);
    Heena.m_data[Direction::Stay].emplace_back(currentStart, size);
    Heena.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Heena.m_data[Direction::Stay].emplace_back(nextStart(), size);

    return Heena;
}

AnimationData SeraData()
{
    const auto size = sf::Vector2i(51, 67);
    const auto initSpace = sf::Vector2i(1082, 10);
    const auto middleSpace = sf::Vector2i(0, 20);

    auto Sera = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Sera.m_data[Direction::Stay].emplace_back(currentStart, size);
    Sera.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Sera.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Sera.m_data[Direction::Stay].emplace_back(currentStart, size);
    Sera.m_data[Direction::Stay].emplace_back(currentStart, size);
    Sera.m_data[Direction::Stay].emplace_back(currentStart, size);
    Sera.m_data[Direction::Stay].emplace_back(currentStart, size);
    Sera.m_data[Direction::Stay].emplace_back(currentStart, size);
    Sera.m_data[Direction::Stay].emplace_back(currentStart, size);
    Sera.m_data[Direction::Stay].emplace_back(currentStart, size);
    Sera.m_data[Direction::Stay].emplace_back(currentStart, size);
    Sera.m_data[Direction::Stay].emplace_back(currentStart, size);

    return Sera;
}

AnimationData PeterData()
{
    const auto size = sf::Vector2i(56, 70);
    const auto initSpace = sf::Vector2i(1228, 10);
    const auto middleSpace = sf::Vector2i(0, 20);

    auto Peter = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Peter.m_data[Direction::Stay].emplace_back(currentStart, size);
    Peter.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Peter.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Peter.m_data[Direction::Stay].emplace_back(currentStart, size);
    Peter.m_data[Direction::Stay].emplace_back(currentStart, size);
    Peter.m_data[Direction::Stay].emplace_back(currentStart, size);
    Peter.m_data[Direction::Stay].emplace_back(currentStart, size);
    Peter.m_data[Direction::Stay].emplace_back(currentStart, size);
    Peter.m_data[Direction::Stay].emplace_back(currentStart, size);
    Peter.m_data[Direction::Stay].emplace_back(currentStart, size);
    Peter.m_data[Direction::Stay].emplace_back(currentStart, size);
    Peter.m_data[Direction::Stay].emplace_back(currentStart, size);

    return Peter;
}

AnimationData TutorialJrSentinelData()
{
    const auto size = sf::Vector2i(56, 90);
    const auto initSpace = sf::Vector2i(1151, 10);
    const auto middleSpace = sf::Vector2i(0, 0);

    auto TutorialJrSentinel = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    TutorialJrSentinel.m_data[Direction::Dead].emplace_back(currentStart, size);
    TutorialJrSentinel.m_data[Direction::Dead].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Dead].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Dead].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Dead].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Hit].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Left].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Right].emplace_back(currentStart, size);
    TutorialJrSentinel.m_data[Direction::Left].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Right].emplace_back(currentStart, size);
    TutorialJrSentinel.m_data[Direction::Left].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Right].emplace_back(currentStart, size);
    TutorialJrSentinel.m_data[Direction::Left].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Right].emplace_back(currentStart, size);
    TutorialJrSentinel.m_data[Direction::Stay].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Stay].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Stay].emplace_back(nextStart(), size);
    TutorialJrSentinel.m_data[Direction::Stay].emplace_back(nextStart(), size);

    return TutorialJrSentinel;
}

AnimationData SnailData()
{
    const auto size = sf::Vector2i(44, 43);
    const auto initSpace = sf::Vector2i(1303, 9);
    const auto middleSpace = sf::Vector2i(0, 10);

    auto Snail = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Snail.m_data[Direction::Dead].emplace_back(currentStart, size);
    Snail.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Hit].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Left].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Right].emplace_back(currentStart, size);
    Snail.m_data[Direction::Left].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Right].emplace_back(currentStart, size);
    Snail.m_data[Direction::Left].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Right].emplace_back(currentStart, size);
    Snail.m_data[Direction::Left].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Right].emplace_back(currentStart, size);
    Snail.m_data[Direction::Left].emplace_back(nextStart(), size);
    Snail.m_data[Direction::Right].emplace_back(currentStart, size);
    Snail.m_data[Direction::Stay].emplace_back(nextStart(), size);

    return Snail;
}

AnimationData BlueSnailData()
{
    const auto size = sf::Vector2i(56, 46);
    const auto initSpace = sf::Vector2i(1368, 9);
    const auto middleSpace = sf::Vector2i(0, 13);

    auto BlueSnail = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    BlueSnail.m_data[Direction::Dead].emplace_back(currentStart, size);
    BlueSnail.m_data[Direction::Dead].emplace_back(nextStart(), size);
    BlueSnail.m_data[Direction::Dead].emplace_back(nextStart(), size);
    BlueSnail.m_data[Direction::Hit].emplace_back(nextStart(), size);
    BlueSnail.m_data[Direction::Left].emplace_back(nextStart(), size);
    BlueSnail.m_data[Direction::Right].emplace_back(currentStart, size);
    BlueSnail.m_data[Direction::Left].emplace_back(nextStart(), size);
    BlueSnail.m_data[Direction::Right].emplace_back(currentStart, size);
    BlueSnail.m_data[Direction::Left].emplace_back(nextStart(), size);
    BlueSnail.m_data[Direction::Right].emplace_back(currentStart, size);
    BlueSnail.m_data[Direction::Left].emplace_back(nextStart(), size);
    BlueSnail.m_data[Direction::Right].emplace_back(currentStart, size);
    BlueSnail.m_data[Direction::Stay].emplace_back(nextStart(), size);

    return BlueSnail;
}

AnimationData ShroomData()
{
    const auto size = sf::Vector2i(45, 44);
    const auto initSpace = sf::Vector2i(1447, 2);
    const auto middleSpace = sf::Vector2i(0, 14);

    auto Shroom = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Shroom.m_data[Direction::Dead].emplace_back(currentStart, size);
    Shroom.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Shroom.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Shroom.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Shroom.m_data[Direction::Hit].emplace_back(nextStart(), size);
    Shroom.m_data[Direction::Left].emplace_back(nextStart(), size);
    Shroom.m_data[Direction::Right].emplace_back(currentStart, size);
    Shroom.m_data[Direction::Left].emplace_back(nextStart(), size);
    Shroom.m_data[Direction::Right].emplace_back(currentStart, size);
    Shroom.m_data[Direction::Left].emplace_back(nextStart(), size);
    Shroom.m_data[Direction::Right].emplace_back(currentStart, size);
    Shroom.m_data[Direction::Left].emplace_back(nextStart(), size);
    Shroom.m_data[Direction::Right].emplace_back(currentStart, size);
    Shroom.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Shroom.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Shroom.m_data[Direction::Stay].emplace_back(nextStart(), size);


    return Shroom;
}

AnimationData StumpData()
{
    const auto size = sf::Vector2i(66, 66);
    const auto initSpace = sf::Vector2i(837, 14);
    const auto middleSpace = sf::Vector2i(0, 11);

    auto Stump = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Stump.m_data[Direction::Dead].emplace_back(currentStart, size);
    Stump.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Stump.m_data[Direction::Dead].emplace_back(nextStart(), size);
    Stump.m_data[Direction::Hit].emplace_back(nextStart(), size);
    Stump.m_data[Direction::Left].emplace_back(nextStart(), size);
    Stump.m_data[Direction::Right].emplace_back(currentStart, size);
    Stump.m_data[Direction::Left].emplace_back(nextStart(), size);
    Stump.m_data[Direction::Right].emplace_back(currentStart, size);
    Stump.m_data[Direction::Left].emplace_back(nextStart(), size);
    Stump.m_data[Direction::Right].emplace_back(currentStart, size);
    Stump.m_data[Direction::Left].emplace_back(nextStart(), size);
    Stump.m_data[Direction::Right].emplace_back(currentStart, size);
    Stump.m_data[Direction::Stay].emplace_back(nextStart(), size);

    return Stump;
}

AnimationData YoonaData()
{
    const auto size = sf::Vector2i(67, 77);
    const auto initSpace = sf::Vector2i(923, 9);
    const auto middleSpace = sf::Vector2i(0, 17);

    auto Yoona = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Yoona.m_data[Direction::Stay].emplace_back(currentStart, size);
    Yoona.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Yoona.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Yoona.m_data[Direction::Stay].emplace_back(currentStart, size);
    Yoona.m_data[Direction::Stay].emplace_back(currentStart, size);
    Yoona.m_data[Direction::Stay].emplace_back(currentStart, size);
    Yoona.m_data[Direction::Stay].emplace_back(currentStart, size);
    Yoona.m_data[Direction::Stay].emplace_back(currentStart, size);
    Yoona.m_data[Direction::Stay].emplace_back(currentStart, size);
    Yoona.m_data[Direction::Stay].emplace_back(currentStart, size);
    Yoona.m_data[Direction::Stay].emplace_back(currentStart, size);
    Yoona.m_data[Direction::Stay].emplace_back(currentStart, size);

    return Yoona;
}

AnimationData LucasData()
{
    const auto size = sf::Vector2i(67, 77);
    const auto initSpace = sf::Vector2i(1655, 9);
    const auto middleSpace = sf::Vector2i(0, 16);

    auto Lucas = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Lucas.m_data[Direction::Stay].emplace_back(currentStart, size);
    Lucas.m_data[Direction::Stay].emplace_back(currentStart, size);
    Lucas.m_data[Direction::Stay].emplace_back(currentStart, size);
    Lucas.m_data[Direction::Stay].emplace_back(currentStart, size);
    Lucas.m_data[Direction::Stay].emplace_back(currentStart, size);
    Lucas.m_data[Direction::Stay].emplace_back(currentStart, size);
    Lucas.m_data[Direction::Stay].emplace_back(currentStart, size);
    Lucas.m_data[Direction::Stay].emplace_back(currentStart, size);
    Lucas.m_data[Direction::Stay].emplace_back(currentStart, size);
    Lucas.m_data[Direction::Stay].emplace_back(currentStart, size);
    Lucas.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Lucas.m_data[Direction::Stay].emplace_back(currentStart, size);

    return Lucas;
}

AnimationData PioData()
{
    const auto size = sf::Vector2i(67, 70);
    const auto initSpace = sf::Vector2i(1007, 9);
    const auto middleSpace = sf::Vector2i(0, 18);

    auto Pio = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Pio.m_data[Direction::Stay].emplace_back(currentStart, size);
    Pio.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Pio.m_data[Direction::Stay].emplace_back(nextStart(), size);

    return Pio;
}

AnimationData BariData()
{
    const auto size = sf::Vector2i(67, 77);
    const auto initSpace = sf::Vector2i(1510, 9);
    const auto middleSpace = sf::Vector2i(0, 17);

    auto Bari = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Bari.m_data[Direction::Stay].emplace_back(currentStart, size);
    Bari.m_data[Direction::Stay].emplace_back(currentStart, size);
    Bari.m_data[Direction::Stay].emplace_back(currentStart, size);
    Bari.m_data[Direction::Stay].emplace_back(currentStart, size);
    Bari.m_data[Direction::Stay].emplace_back(currentStart, size);
    Bari.m_data[Direction::Stay].emplace_back(currentStart, size);
    Bari.m_data[Direction::Stay].emplace_back(currentStart, size);
    Bari.m_data[Direction::Stay].emplace_back(currentStart, size);
    Bari.m_data[Direction::Stay].emplace_back(currentStart, size);
    Bari.m_data[Direction::Stay].emplace_back(currentStart, size);
    Bari.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Bari.m_data[Direction::Stay].emplace_back(nextStart(), size);

    return Bari;
}

AnimationData BiggsData()
{
    const auto size = sf::Vector2i(46, 70);
    const auto initSpace = sf::Vector2i(1727, 9);
    const auto middleSpace = sf::Vector2i(0, 17);

    auto Biggs = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Biggs.m_data[Direction::Stay].emplace_back(currentStart, size);
    Biggs.m_data[Direction::Stay].emplace_back(nextStart(), size);
    Biggs.m_data[Direction::Stay].emplace_back(currentStart, size);
    Biggs.m_data[Direction::Stay].emplace_back(currentStart, size);
    Biggs.m_data[Direction::Stay].emplace_back(currentStart, size);
    Biggs.m_data[Direction::Stay].emplace_back(currentStart, size);
    Biggs.m_data[Direction::Stay].emplace_back(currentStart, size);
    Biggs.m_data[Direction::Stay].emplace_back(currentStart, size);
    Biggs.m_data[Direction::Stay].emplace_back(currentStart, size);
    Biggs.m_data[Direction::Stay].emplace_back(currentStart, size);
    Biggs.m_data[Direction::Stay].emplace_back(currentStart, size);
    Biggs.m_data[Direction::Stay].emplace_back(currentStart, size);

    return Biggs;
}

AnimationData ShanksData()
{
    const auto size = sf::Vector2i(75, 79);
    const auto initSpace = sf::Vector2i(1775, 0);
    const auto middleSpace = sf::Vector2i(0, 15);

    auto Shanks = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.y += size.y;
        return currentStart;
    };

    // animations
    Shanks.m_data[Direction::Stay].emplace_back(currentStart, size);

    return Shanks;
}

Resources& Resources::instance()
{
    static Resources instance;
    return instance;
}

Resources::Resources()
    : m_data(Max)
{
    loadAnimations();
    loadBackgrounds();
    loadMaps();
    loadTextures();
    loadMusic();
    loadSound();
    loadDialogue();
}

void Resources::loadAnimations()
{
    // load animations
    if (!m_texture.loadFromFile("resources/Animations.png"))
        throw std::runtime_error("Can't load file");

    m_data[Player] = playerData();
    m_data[Mushroom] = MushroomData();
    m_data[Portal] = PortalData();
    m_data[LevelUp] = LevelUpData();
    m_data[Tombstone] = TombstoneData();
    m_data[Heena] = HeenaData();
    m_data[Sera] = SeraData();
    m_data[Peter] = PeterData();
    m_data[TutorialJrSentinel] = TutorialJrSentinelData();
    m_data[Snail] = SnailData();
    m_data[BlueSnail] = BlueSnailData();
    m_data[Shroom] = ShroomData();
    m_data[Maria] = SeraData();
    m_data[Stump] = StumpData();
    m_data[Yoona] = YoonaData();
    m_data[Rain] = HeenaData();
    m_data[Pio] = PioData();
    m_data[Maria2] = SeraData();
    m_data[Lucas] = LucasData();
    m_data[Bari] = BariData();
    m_data[Biggs] = BiggsData();
    m_data[Shanks] = ShanksData();
}

void Resources::loadBackgrounds()
{
    if (!m_backgrounds[MushroomTown].loadFromFile("resources/Background1.jpg")   ||
        !m_backgrounds[SmallForest].loadFromFile("resources/Background1.jpg")    ||
        !m_backgrounds[SplitRoad].loadFromFile("resources/Background2.png")      ||
        !m_backgrounds[WestAmherst].loadFromFile("resources/Background2.png")    ||
        !m_backgrounds[Amherst].loadFromFile("resources/Background1.jpg")        ||
        !m_backgrounds[WestSouthperry].loadFromFile("resources/Background2.png") ||
        !m_backgrounds[Southperry].loadFromFile("resources/Background3.jpg")      )
        throw std::runtime_error("Can't load background");
}

void Resources::loadMaps()
{
    if (!m_maps[MushroomTown].loadFromFile("resources/MushroomTown.png")      ||
        !m_maps[SmallForest].loadFromFile("resources/SmallForest.png")        ||
        !m_maps[SplitRoad].loadFromFile("resources/SplitRoad.png")            ||
        !m_maps[WestAmherst].loadFromFile("resources/WestAmherst.png")        ||
        !m_maps[Amherst].loadFromFile("resources/Amherst.png")                ||
        !m_maps[WestSouthperry].loadFromFile("resources/WestSouthperry.png")  ||
        !m_maps[Southperry].loadFromFile("resources/Southperry.png")           )
        throw std::runtime_error("Can't load map");
}

void Resources::loadTextures()
{
    if (!m_textures[MenuBackground].loadFromFile("resources/MenuBackground1.jpg")                  ||
        !m_textures[Ground].loadFromFile("resources/Ground.png")                                   ||
        !m_textures[Wall].loadFromFile("resources/Wall.png")                                       ||
        !m_textures[MonsterWall].loadFromFile("resources/MonsterWall.png")                         ||
        !m_textures[Ladder].loadFromFile("resources/Ladder.png")                                   ||
        !m_textures[Rope].loadFromFile("resources/Rope.png")                                       ||
        !m_textures[Panel].loadFromFile("resources/Panel.png")                                     ||
        !m_textures[Revive].loadFromFile("resources/Revive.png")                                   ||
        !m_textures[Dialogue].loadFromFile("resources/Dialogue.png")                               ||
        !m_textures[Tutorial].loadFromFile("resources/Tutorial.png")                               ||
        !m_textures[Cursor].loadFromFile("resources/Cursor.png")                                   ||
        !m_textures[OK_Button].loadFromFile("resources/OK_Button.png")                             ||
        !m_textures[OK_Button_Highlighted].loadFromFile("resources/OK_Button_Highlighted.png")     ||
        !m_textures[OK_Button_Pressed].loadFromFile("resources/OK_Button_Pressed.png")             ||
        !m_textures[NEXT_Button].loadFromFile("resources/NEXT_Button.png")                         ||
        !m_textures[NEXT_Button_Highlighted].loadFromFile("resources/NEXT_Button_Highlighted.png") ||
        !m_textures[NEXT_Button_Pressed].loadFromFile("resources/NEXT_Button_Pressed.png")         ||
        !m_textures[BACK_Button].loadFromFile("resources/BACK_Button.png")                         ||
        !m_textures[BACK_Button_Highlighted].loadFromFile("resources/BACK_Button_Highlighted.png") ||
        !m_textures[BACK_Button_Pressed].loadFromFile("resources/BACK_Button_Pressed.png")         ||
        !m_textures[YES_Button].loadFromFile("resources/YES_Button.png")                           ||
        !m_textures[YES_Button_Highlighted].loadFromFile("resources/YES_Button_Highlighted.png")   ||
        !m_textures[YES_Button_Pressed].loadFromFile("resources/YES_Button_Pressed.png")           ||
        !m_textures[NO_Button].loadFromFile("resources/NO_Button.png")                             ||
        !m_textures[NO_Button_Highlighted].loadFromFile("resources/NO_Button_Highlighted.png")     ||
        !m_textures[NO_Button_Pressed].loadFromFile("resources/NO_Button_Pressed.png")             ||
        !m_textures[END_Button].loadFromFile("resources/END_Button.png")                           ||
        !m_textures[END_Button_Highlighted].loadFromFile("resources/END_Button_Highlighted.png")   ||
        !m_textures[END_Button_Pressed].loadFromFile("resources/END_Button_Pressed.png")           ||
        !m_textures[Arrival_Texture].loadFromFile("resources/Arrival.png")                          )
        throw std::runtime_error("Can't load texture");
}

void Resources::loadMusic()
{
    if (!m_music[Menu].loadFromFile("resources/Intro.wav")            || 
        !m_music[MushroomTown].loadFromFile("resources/music1.wav")   ||
        !m_music[SmallForest].loadFromFile("resources/music1.wav")    ||
        !m_music[SplitRoad].loadFromFile("resources/music2.wav")      ||
        !m_music[WestAmherst].loadFromFile("resources/music2.wav")    ||
        !m_music[Amherst].loadFromFile("resources/music1.wav")        ||
        !m_music[WestSouthperry].loadFromFile("resources/music2.wav") ||
        !m_music[Southperry].loadFromFile("resources/music3.wav")      )
        
        throw std::runtime_error("Can't load music");
}

void Resources::loadSound()
{
    if (!m_sound[Death_Sound].loadFromFile("resources/death.wav")                                       ||
        !m_sound[LevelUp_Sound].loadFromFile("resources/LevelUp.wav")                                   ||
        !m_sound[HitSound1].loadFromFile("resources/hitSound1.wav")                                     ||
        !m_sound[Sword_Sound].loadFromFile("resources/sword.wav")                                       ||
        !m_sound[Jump_Sound].loadFromFile("resources/jump.wav")                                         ||
        !m_sound[Arrival].loadFromFile("resources/Arrival.wav")                                         ||
        !m_sound[TutorialJrSentinelDeath_Sound].loadFromFile("resources/tutorialJrSentinel_death.wav")  ||
        !m_sound[TutorialJrSentinelHit_Sound].loadFromFile("resources/tutorialJrSentinel_hit.wav")      ||
        !m_sound[SnailDeath_Sound].loadFromFile("resources/snail_death.wav")                            ||
        !m_sound[SnailHit_Sound].loadFromFile("resources/snail_hit.wav")                                ||
        !m_sound[ShroomDeath_Sound].loadFromFile("resources/shroom_death.wav")                          ||
        !m_sound[StumpDeath_Sound].loadFromFile("resources/stump_death.wav")                            ||
        !m_sound[StumpHit_Sound].loadFromFile("resources/stump_hit.wav")                                ||
        !m_sound[MushroomDeath_Sound].loadFromFile("resources/mushroom_death.wav")                      ||
        !m_sound[Portal_Sound].loadFromFile("resources/Portal.wav")                                      )
        throw std::runtime_error("Can't load sound");
}

void Resources::loadDialogue()
{
    m_font.loadFromFile("resources/arial.ttf");

    m_dialogue[Heena].push_back(std::make_shared<sf::Text>("Hello there. You must be a newcomer. Glad to meet you. \nI guess you're still unfamiliar with Mushroom World. \nDo not worry, we welcome you here with open arms.", m_font, 13));
    m_dialogue[Heena].push_back(std::make_shared<sf::Text>("Come to think of it, my sister Sera said that \nshe wanted to talk to new travellers... \nIf you don't mind, please go and send Sera my regards.", m_font, 13));
    m_dialogue[Heena].push_back(std::make_shared<sf::Text>("I wish you good luck on your adventures out there!", m_font, 13));
    m_dialogue[Sera].push_back(std::make_shared<sf::Text>("...oh, hello! You must be a newcomer. \nHeena must have told you about me. I'm so glad we met.", m_font, 13));
    m_dialogue[Sera].push_back(std::make_shared<sf::Text>("Mushroom World may be a small island, but I think it's \nreally great that I can be the first to meet new travelers. \nI think there's nothing better than becoming friends with \nstrangers. I hope you will make a lot of friends while you \nare here.", m_font, 13));
    m_dialogue[Sera].push_back(std::make_shared<sf::Text>("If you wish to proceed, please use the portal on the right. \nThe shining ray of light is called a portal. \nYou can travel by standing on it and pressing the \nup arrow key. Farewell, now... I hope your future is bright.", m_font, 13));
    m_dialogue[Peter].push_back(std::make_shared<sf::Text>("Oh, a new traveler! Hey there, my name is Peter. This is \nwhere I teach new travelers like you how to hunt monsters. \nIt'll be quite dangerous for you to go out there, if you aren't \nwell-prepared for it.", m_font, 13));
    m_dialogue[Peter].push_back(std::make_shared<sf::Text>("You see the Jr. Sentinel there? Try attacking it. \nNormally it's a powerful monster, but Grendel the Really \nOld, the head of all magicians, put a seal on it just for \nbeginners like you, so you'll have no trouble practicing \nyour swings against it.", m_font, 13));
    m_dialogue[Peter].push_back(std::make_shared<sf::Text>("To hit the Jr. Sentinel you'll have to press CTRL, \ngood luck!", m_font, 13));
    m_dialogue[Maria].push_back(std::make_shared<sf::Text>("I'm not Sera, you probably mistaken me for my twin sister.", m_font, 13));
    m_dialogue[Maria].push_back(std::make_shared<sf::Text>("Watch out for monsters ahead, they may be quite tough \nfor newcomers.", m_font, 13));
    m_dialogue[Yoona].push_back(std::make_shared<sf::Text>("Oh hello! Already lost are we?", m_font, 13));
    m_dialogue[Yoona].push_back(std::make_shared<sf::Text>("Amherst you say? Well you got the right person!", m_font, 13));
    m_dialogue[Yoona].push_back(std::make_shared<sf::Text>("Just go to the portal on your right and \nyou'll be there in no time!", m_font, 13));
    m_dialogue[Rain].push_back(std::make_shared<sf::Text>("Sorry... not in the mood right now.", m_font, 13));
    m_dialogue[Pio].push_back(std::make_shared<sf::Text>("NO! I'M NOT BOB THE BUILDER!!!", m_font, 13));
    m_dialogue[Maria2].push_back(std::make_shared<sf::Text>("My my.. looks like you've found your way here!", m_font, 13));
    m_dialogue[Maria2].push_back(std::make_shared<sf::Text>("Hope you enjoy your time at Amherst!", m_font, 13));
    m_dialogue[Lucas].push_back(std::make_shared<sf::Text>("A way out here you say? Well glad you asked!", m_font, 13));
    m_dialogue[Lucas].push_back(std::make_shared<sf::Text>("My grandson Shanks in Southperry has a ship. \nI'm sure he'll give you a ride.", m_font, 13));
    m_dialogue[Bari].push_back(std::make_shared<sf::Text>("Our ship is almost ready to set sail.", m_font, 13));
    m_dialogue[Bari].push_back(std::make_shared<sf::Text>("Our captain? He's probably somewhere in Southperry.", m_font, 13));
    m_dialogue[Bari].push_back(std::make_shared<sf::Text>("Don't be like that, our captain is nice. \nI'm sure he'll let you sail with us.", m_font, 13));
    m_dialogue[Bari].push_back(std::make_shared<sf::Text>("To get to Southperry take the portal on your right, \nour captain Shanks must be there.", m_font, 13));
    m_dialogue[Biggs].push_back(std::make_shared<sf::Text>("What a clear sky... Finally some fresh air!", m_font, 13));
    m_dialogue[Biggs].push_back(std::make_shared<sf::Text>("Huh? Who you lookin at?", m_font, 13));
    m_dialogue[Biggs].push_back(std::make_shared<sf::Text>("Shanks? He must be at our ship.. \nKeep walking right he'll be there.", m_font, 13));
    m_dialogue[Shanks].push_back(std::make_shared<sf::Text>("Yo!", m_font, 13));
    m_dialogue[Shanks].push_back(std::make_shared<sf::Text>("You know my grandfather?!", m_font, 13));
    m_dialogue[Shanks].push_back(std::make_shared<sf::Text>("Very well.. I'll give u a ride to Victoria Island.", m_font, 13));
    m_dialogue[Shanks].push_back(std::make_shared<sf::Text>("Are you ready to go? (Level 10 required)", m_font, 13));
    m_dialogue[Shanks].push_back(std::make_shared<sf::Text>("Not sure you have trained enough for this journey.", m_font, 13));
}
