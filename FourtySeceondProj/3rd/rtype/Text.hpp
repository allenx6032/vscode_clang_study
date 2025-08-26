/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Color.hpp"
#include "Rect.hpp"
#include "Vector2.hpp"
#include "Config.hpp"
#include "Font.hpp"
#include <sfml/SFML_Text.hpp>

namespace gameEngine {
    class Text {

        enum Style
        {
            Regular       = 0,      // <-- Regular characters, no style
            Bold          = 1 << 0, // <-- Bold characters
            Italic        = 1 << 1, // <-- Italic characters
            Underlined    = 1 << 2, // <-- Underlined characters
            StrikeThrough = 1 << 3  // <-- Strike through characters
        };

        public:
            Text() :
                _text()
            {
            };
            Text(Font& font, const std::string& string = "", unsigned int characterSize = 30) :
                _text()
            {
                setFont(font);
                setString(string);
                setCharacterSize(characterSize);
            };

            void setFont(Font& font) {
                _text.setFont(font.getSfmlFont());
                _font = &font;
            };
            void setString(const std::string& string) { _text.setString(string); };
            void setCharacterSize(unsigned int size) { _text.setCharacterSize(size); };
            void setLineSpacing(float spacingFactor) { _text.setLineSpacing(spacingFactor); };
            void setLetterSpacing(float spacingFactor) { _text.setLetterSpacing(spacingFactor); };
            void setStyle(Uint32 style) { _text.setStyle(style); };
            void setFillColor(const Color& color) { _text.setFillColor(color); };
            void setOutlineColor(const Color& color) { _text.setOutlineColor(color); };
            void setOutlineThickness(float thickness) { _text.setOutlineThickness(thickness); };

            const Font* getFont() const { return _font; };
            const std::string getString() const { return _text.getString(); };
            unsigned int getCharacterSize() const { return _text.getCharacterSize(); };
            float getLetterSpacing() const { return _text.getLetterSpacing(); };
            float getLineSpacing() const { return _text.getLineSpacing(); };
            Uint32 getStyle() const { return _text.getStyle(); };
            const Color getFillColor() const { return _text.getFillColor(); };
            const Color getOutlineColor() const { return _text.getOutlineColor(); };
            float getOutlineThickness() const { return _text.getOutlineThickness(); };
            Vector2f findCharacterPos(std::size_t index) const { return _text.findCharacterPos(index); };
            FloatRect getLocalBounds() const { return _text.getLocalBounds(); };
            FloatRect getGlobalBounds() const { return _text.getGlobalBounds(); };

            void setOrigin(const Vector2f& origin) { _text.setOrigin(origin); };
            void setOrigin(float x, float y) { _text.setOrigin(x, y); };
            void setPosition(const Vector2f& position) { _text.setPosition(position); };
            void setPosition(float x, float y) { _text.setPosition(x, y); };
            void move(const Vector2f& offset) { _text.move(offset); };
            void rotate(float angle) { _text.rotate(angle); };
            void scale(const Vector2f& factors) { _text.scale(factors); };
            void setScale(const Vector2f& factors) { _text.setScale(factors); };
            void setScale(float factorX, float factorY) { _text.setScale(factorX, factorY); };
            void setRotation(float angle) { _text.setRotation(angle); };

            const sf::Text& getSfmlText() const { return _text; };

        public:
            Text(const sf::Text& text) :
                _text(text)
            {
            };

            operator sf::Text() const { return _text; };

        private:
            Font *_font;
            sf::Text _text;
    };
}