/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Vector2.hpp"
#include <sfml/SFML_Texture.hpp>

namespace gameEngine {
    class Texture {
        public:
            Texture() :
                _texture()
            {
            };
            Texture(const Texture& texture) :
                _texture(texture._texture)
            {
            };
            Texture(const std::string& filename) :
                _texture()
            {
                loadFromFile(filename);
            };

            bool loadFromFile(const std::string& filename) { return _texture.loadFromFile(filename); };
            bool loadFromMemory(const void* data, std::size_t size) { return _texture.loadFromMemory(data, size); };
            bool loadFromStream(sf::InputStream& stream) { return _texture.loadFromStream(stream); };
            bool loadFromImage(const sf::Image& image) { return _texture.loadFromImage(image); };

            void setSmooth(bool smooth) { _texture.setSmooth(smooth); };
            bool isSmooth() const { return _texture.isSmooth(); };

            void setSrgb(bool sRgb) { _texture.setSrgb(sRgb); };
            bool isSrgb() const { return _texture.isSrgb(); };

            void setRepeated(bool repeated) { _texture.setRepeated(repeated); };
            bool isRepeated() const { return _texture.isRepeated(); };

            static unsigned int getMaximumSize() { return sf::Texture::getMaximumSize(); };

            Vector2u getSize() const {
                sf::Vector2u size = _texture.getSize();
                return Vector2u(size.x, size.y);
            };

            const sf::Texture& getSfmlTexture() const { return _texture; };

        public:
            Texture(const sf::Texture& texture) :
                _texture(texture)
            {
            };

            operator sf::Texture() const { return _texture; };

        private:
            sf::Texture _texture;
    };
}