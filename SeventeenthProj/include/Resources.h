#pragma once

#include "AnimationData.h"
#include <SFML/SFML_graphics.hpp>
#include <SFML/SFML_Audio.hpp>
#include <vector>

class Resources
{
public:
    // ---------------
    enum Objects
    {
        Mushroom,
        Player,
        Portal,
        LevelUp,
        Tombstone,
        Heena,
        Sera,
        Peter,
        Maria,
        TutorialJrSentinel,
        Snail,
        BlueSnail,
        Shroom,
        Stump,
        Yoona,
        Rain,
        Pio,
        Maria2,
        Lucas,
        Bari,
        Biggs,
        Shanks,
        Max,
    };
    // ---------------
    enum Textures
    {
        MenuBackground,
        Ground,
        Wall,
        MonsterWall,
        Ladder,
        Rope,
        Panel,
        Revive,
        Dialogue,
        OK_Button,
        OK_Button_Highlighted,
        OK_Button_Pressed,
        NEXT_Button,
        NEXT_Button_Highlighted,
        NEXT_Button_Pressed,
        BACK_Button,
        BACK_Button_Highlighted,
        BACK_Button_Pressed,
        YES_Button,
        YES_Button_Highlighted,
        YES_Button_Pressed,
        NO_Button,
        NO_Button_Highlighted,
        NO_Button_Pressed,
        END_Button,
        END_Button_Highlighted,
        END_Button_Pressed,
        Cursor,
        Tutorial,
        Arrival_Texture
    };
    // ---------------
    enum Maps
    {
        Menu,
        MushroomTown,
        SmallForest,
        SplitRoad,
        WestAmherst,
        Amherst,
        WestSouthperry,
        Southperry,
    };
    // ---------------
    enum Sound
    {
        Death_Sound,
        LevelUp_Sound,
        HitSound1,
        Sword_Sound,
        Jump_Sound,
        Arrival,
        TutorialJrSentinelDeath_Sound,
        TutorialJrSentinelHit_Sound,
        MushroomDeath_Sound,
        SnailDeath_Sound,
        SnailHit_Sound,
        ShroomDeath_Sound,
        StumpDeath_Sound,
        StumpHit_Sound,
        Portal_Sound,
    };

    static Resources& instance();

    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    const sf::Texture& texture() const { return m_texture; }
    const sf::Font& font() const { return m_font; }
    const sf::Texture& texture(int i) const { return m_textures.at(i); }
    const sf::Texture& backgrounds(int i) const { return m_backgrounds.at(i); }
    const sf::Texture& maps(int i) const { return m_maps.at(i); }
    const sf::SoundBuffer& music(int i) const { return m_music.at(i); }
    const sf::SoundBuffer& sound(int i) const { return m_sound.at(i); }
    const AnimationData& animationData(Objects object) { return m_data[object]; }
    const std::vector<std::shared_ptr<sf::Text>>& dialogues(Objects object) { return m_dialogue[object]; }

private:
    Resources();
    void loadAnimations();
    void loadBackgrounds();
    void loadMaps();
    void loadTextures();
    void loadMusic();
    void loadSound();
    void loadDialogue();

    sf::Texture m_texture;
    sf::Font m_font;
    std::unordered_map<int, sf::Texture> m_textures;
    std::unordered_map<int, sf::Texture> m_backgrounds;
    std::unordered_map<int, sf::Texture> m_maps;
    std::unordered_map<int, sf::SoundBuffer> m_music;
    std::unordered_map<int, sf::SoundBuffer> m_sound;
    std::unordered_map<int, std::vector<std::shared_ptr<sf::Text>>> m_dialogue;
    std::vector<AnimationData> m_data;
};
