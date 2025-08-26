/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Vector2.hpp"
#include "Rect.hpp"
#include "Angle.hpp"
#include <cmath>
#include <sfml/SFML_View.hpp>

namespace gameEngine {
    class View {
        public:
            View() :
                _view()
            {
            };
            View(const FloatRect &rect) :
                _view(rect)
            {
            };
            View(const Vector2f &center, const Vector2f &size) :
                _view(center, size)
            {
            };

            void setCenter(const Vector2f &center) { _view.setCenter(center); };
            void setCenter(float x, float y) { _view.setCenter(x, y); };
            const Vector2f getCenter() const {
                sf::Vector2f center = _view.getCenter();
                return Vector2f(center.x, center.y);
            };

            void setSize(const Vector2f &size) { _view.setSize(size); };
            void setSize(float width, float height) { _view.setSize(width, height); };
            const Vector2f getSize() const {
                sf::Vector2f size = _view.getSize();
                return Vector2f(size.x, size.y);
            };

            void setViewport(const FloatRect &viewport) { _view.setViewport(viewport); };
            void setViewport(float left, float top, float width, float height) { _view.setViewport(FloatRect(left, top, width, height)); };
            const FloatRect getViewport() const {
                sf::FloatRect viewport = _view.getViewport();
                return FloatRect(viewport.left, viewport.top, viewport.width, viewport.height);
            };

            void setRotation(Angle angle) { _view.setRotation(angle); };
            void setRotation(float angle) { _view.setRotation(angle); };
            Angle getRotation() const {
                return Angle(_view.getRotation());
            };

            void move(const Vector2f &offset) { _view.move(offset); };
            void move(float offsetX, float offsetY) { _view.move(offsetX, offsetY); };
            void rotate(Angle angle) { _view.rotate(angle); };
            void zoom(float factor) { _view.zoom(factor); };

            sf::View &getSfmlView() { return _view; };

        public:
            operator sf::View() const { return _view; };

            View(const sf::View &view) :
                _view(view)
            {
            };

        private:
            sf::View _view;
    };
}
