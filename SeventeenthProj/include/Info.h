#pragma once

#include "Map.h"
#include "Damage.h"
#include "ReviveGUI.h"
#include "TutorialGUI.h"
#include "DialogueGUI.h"
#include "ArrivalGUI.h"

class Info
{
public:
    // ---------------
    enum GUI_List
    {
        Revive,
        Tutorial,
        Arrival,
    };
    // ---------------

    static Info& instance();
    void drawGUI(sf::RenderWindow& window);
    void update(const Data& data);
    void showDamage(const std::string& type, const int& amount, const sf::Vector2f& location);
    void addGUI(const int& type);
    void showDialogue(const Resources::Objects& dialogue, const sf::Text& name, std::shared_ptr<sf::Sprite> sprite);
    void drawInfo(sf::RenderWindow& window);

    Info(const Info&) = delete;
    Info& operator=(const Info&) = delete;

private:
    Info();
    void init(sf::Text& text, const int& size, const sf::Vector2f& position);
    void init(sf::RectangleShape& bar, const sf::Color& color,
              const sf::Vector2f& position, const sf::Vector2f& size);

    // Damage
    std::vector<std::unique_ptr<Damage>> damageInfo;    // holds all damage objects
    std::vector<std::unique_ptr<GUI>> GUIs;              // holds all GUI objects

    // Text
    sf::Text level;
    sf::Text HP;
    sf::Text MP;
    sf::Text EXP;
    sf::Text job;

    // Graphics
    sf::Sprite panel;
    sf::RectangleShape HPbar;
    sf::RectangleShape MPbar;
    sf::RectangleShape EXPbar;
    sf::RectangleShape background1;
    sf::RectangleShape background2;
    sf::RectangleShape background3;
};
