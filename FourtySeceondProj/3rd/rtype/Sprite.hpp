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
#include "Texture.hpp"
#include <sfml/SFML_Sprite.hpp>

namespace gameEngine {
    class Sprite {
        public:
            Sprite() :
                _sprite()
            {
            };
            Sprite(Texture& texture)
            {
                setTexture(texture);
            };
            Sprite(Texture& texture, const IntRect& rectangle)
            {
                setTexture(texture);
                setTextureRect(rectangle);
            };

            void setTexture(Texture& texture, bool resetRect = false) {
                _sprite.setTexture(texture.getSfmlTexture(), resetRect);
                _texture = &texture;
            };
            const Texture* getTexture() const { return _texture; };

            void setTextureRect(const IntRect& rectangle) { _sprite.setTextureRect(rectangle); };
            const IntRect getTextureRect() const {
                sf::IntRect rectangle = _sprite.getTextureRect();
                return IntRect(rectangle.left, rectangle.top, rectangle.width, rectangle.height);
            };

            void setColor(const Color& color) { _sprite.setColor(color); };
            const Color getColor() const {
                sf::Color color = _sprite.getColor();
                return Color(color.r, color.g, color.b, color.a);
            };

            void setPosition(const Vector2f& position) { _sprite.setPosition(position); };
            void setPosition(float x, float y) { _sprite.setPosition(x, y); };
            const Vector2f getPosition() const {
                sf::Vector2f position = _sprite.getPosition();
                return Vector2f(position.x, position.y);
            };

            void setRotation(float angle) { _sprite.setRotation(angle); };
            float getRotation() const { return _sprite.getRotation(); };

            void setScale(const Vector2f& scale) { _sprite.setScale(scale); };
            void setScale(float x, float y) { _sprite.setScale(x, y); };
            const Vector2f getScale() const {
                sf::Vector2f scale = _sprite.getScale();
                return Vector2f(scale.x, scale.y);
            };

            void setOrigin(const Vector2f& origin) { _sprite.setOrigin(origin); };
            void setOrigin(float x, float y) { _sprite.setOrigin(x, y); };
            const Vector2f getOrigin() const {
                sf::Vector2f origin = _sprite.getOrigin();
                return Vector2f(origin.x, origin.y);
            };

            void move(const Vector2f& offset) { _sprite.move(offset); };
            void move(float offsetX, float offsetY) { _sprite.move(offsetX, offsetY); };
            void rotate(float angle) { _sprite.rotate(angle); };
            void scale(const Vector2f& factor) { _sprite.scale(factor); };
            void scale(float factorX, float factorY) { _sprite.scale(factorX, factorY); };

            const FloatRect getGlobalBounds() const {
                sf::FloatRect rect = _sprite.getGlobalBounds();
                return FloatRect(rect.left, rect.top, rect.width, rect.height);
            };
            const FloatRect getLocalBounds() const {
                sf::FloatRect rect = _sprite.getLocalBounds();
                return FloatRect(rect.left, rect.top, rect.width, rect.height);
            };

        public:
            Sprite(const sf::Sprite& sprite) :
                _sprite(sprite)
            {
            };

            operator sf::Sprite() const { return _sprite; };

        private:
            Texture *_texture;
            sf::Sprite _sprite;
    };
}