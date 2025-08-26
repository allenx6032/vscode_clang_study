/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include <sfml/SFML_Font.hpp>

namespace gameEngine {
    class Font {
        public:
            Font() :
                _font()
            {
            };
            Font(const Font& font) :
                _font(font._font)
            {
            };
            Font(const std::string& filename) :
                _font()
            {
                loadFromFile(filename);
            };

            bool loadFromFile(const std::string& filename) { return _font.loadFromFile(filename); };
            bool loadFromMemory(const void* data, std::size_t size) { return _font.loadFromMemory(data, size); };
            bool loadFromStream(sf::InputStream& stream) { return _font.loadFromStream(stream); };

            const sf::Font& getSfmlFont() const { return _font; };

        public:
            Font(const sf::Font& font) :
                _font(font)
            {
            };

            operator sf::Font() const { return _font; };

        private:
            sf::Font _font;
    };
}