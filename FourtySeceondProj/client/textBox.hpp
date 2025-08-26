/*
** EPITECH PROJECT, 2023
** textbox
** File description:
** textbox
*/

#pragma once

#include "rtype/gameEngine.hpp"
#include "rtype/init.hpp"
#include "rtype/systemCustom.hpp"
#include <sfml/SFML_Graphics.hpp>
#include <chrono>

#define TEXTBOX_FONT_SIZE 20
#define TEXTBOX_WIDTH 400
#define TEXTBOX_HEIGHT 100
#define TEXTBOX_TEXT_OFFSETX 30
#define TEXTBOX_TEXT_OFFSETY 20

class TextBox {
    public:
        TextBox(GameEngine &ge, size_t maxSize = 10, std::string basic = "") : _ge(ge), _inputText(std::move(basic)), _maxSize(maxSize) {};
        ~TextBox() = default;

    public:

        Entity init(float posx, float posy, sf::Font &font, float scalex = 1, float scaley = 1, int offsetX = TEXTBOX_TEXT_OFFSETX, int offsetY = TEXTBOX_TEXT_OFFSETY);

        void update(gameEngine::Event &event);

        sf::Text &getText();

        std::vector<float> getPos() { return { _posX, _posY }; };

        sf::IntRect getRect() { return _rect; };

        std::string &getInputText() { return _inputText; };

        void changeTexture(std::string textureName);

        void draw(gameEngine::RenderWindow &window) { window.draw(_text); };

    public:
        sf::Text _text;
    private:
        GameEngine &_ge;
        size_t _entity;
        std::string _inputText;
        size_t _maxSize;
        float _posX;
        float _posY;
        sf::IntRect _rect;
} ;