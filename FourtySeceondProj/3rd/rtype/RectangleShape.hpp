/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Color.hpp"
#include "Vector2.hpp"
#include "Rect.hpp"
#include "Angle.hpp"
#include "Texture.hpp"
#include <sfml/SFML_RectangleShape.hpp>

namespace gameEngine {
    class RectangleShape {
        public:
            RectangleShape() :
                _rectangleShape()
            {
            };
            RectangleShape(const Vector2f &size) :
                _rectangleShape(size)
            {
            };
            RectangleShape(const Vector2f &size, const Color &color) :
                _rectangleShape(size)
            {
                _rectangleShape.setFillColor(color);
            };
            RectangleShape(const Vector2f &size, const Texture &texture) :
                _rectangleShape(size)
            {
                _rectangleShape.setTexture(&texture.getSfmlTexture());
            };

            void setSize(const Vector2f &size) { _rectangleShape.setSize(size); };
            void setSize(float width, float height) { _rectangleShape.setSize(sf::Vector2f(width, height)); };
            const Vector2f getSize() const {
                sf::Vector2f size = _rectangleShape.getSize();
                return Vector2f(size.x, size.y);
            };

            void setTexture(const Texture &texture) { _rectangleShape.setTexture(&texture.getSfmlTexture()); };
            const Texture *getTexture() const {
                const sf::Texture *texture = _rectangleShape.getTexture();
                return reinterpret_cast<const Texture *>(texture);
            };

            void setFillColor(const Color &color) { _rectangleShape.setFillColor(color); };
            const Color getFillColor() const {
                sf::Color color = _rectangleShape.getFillColor();
                return Color(color.r, color.g, color.b, color.a);
            };

            void setOutlineColor(const Color &color) { _rectangleShape.setOutlineColor(color); };
            const Color getOutlineColor() const {
                sf::Color color = _rectangleShape.getOutlineColor();
                return Color(color.r, color.g, color.b, color.a);
            };

            void setOutlineThickness(float thickness) { _rectangleShape.setOutlineThickness(thickness); };
            float getOutlineThickness() const { return _rectangleShape.getOutlineThickness(); };

            void setOrigin(const Vector2f &origin) { _rectangleShape.setOrigin(origin); };
            void setOrigin(float x, float y) { _rectangleShape.setOrigin(x, y); };
            const Vector2f getOrigin() const {
                sf::Vector2f origin = _rectangleShape.getOrigin();
                return Vector2f(origin.x, origin.y);
            };

            void setPosition(const Vector2f &position) { _rectangleShape.setPosition(position); };
            void setPosition(float x, float y) { _rectangleShape.setPosition(x, y); };
            const Vector2f getPosition() const {
                sf::Vector2f position = _rectangleShape.getPosition();
                return Vector2f(position.x, position.y);
            };

            void setRotation(Angle angle) { _rectangleShape.setRotation(angle); };
            void setRotation(float angle) { _rectangleShape.setRotation(angle); };
            Angle getRotation() const {
                return Angle(_rectangleShape.getRotation());
            };

            void move(const Vector2f &offset) { _rectangleShape.move(offset); };
            void move(float offsetX, float offsetY) { _rectangleShape.move(offsetX, offsetY); };
            void rotate(Angle angle) { _rectangleShape.rotate(angle); };

            void scale(const Vector2f &factor) { _rectangleShape.scale(factor); };
            void scale(float factorX, float factorY) { _rectangleShape.scale(factorX, factorY); };

            const FloatRect getGlobalBounds() const {
                sf::FloatRect rect = _rectangleShape.getGlobalBounds();
                return FloatRect(rect.left, rect.top, rect.width, rect.height);
            };
            const FloatRect getLocalBounds() const {
                sf::FloatRect rect = _rectangleShape.getLocalBounds();
                return FloatRect(rect.left, rect.top, rect.width, rect.height);
            };

            sf::RectangleShape &getSfmlRectangleShape() { return _rectangleShape; };

        public:
            operator sf::RectangleShape() const { return _rectangleShape; };

            RectangleShape(const sf::RectangleShape &rectangleShape) :
                _rectangleShape(rectangleShape)
            {
            };

        private:
            sf::RectangleShape _rectangleShape;
    };
}