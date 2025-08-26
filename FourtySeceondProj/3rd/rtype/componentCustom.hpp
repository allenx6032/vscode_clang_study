/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Component custom
*/

#pragma once
#include <iostream>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

namespace component {
    struct Mass {
        float _mass;

        friend std::ostream &operator<<(std::ostream &os, const Mass &mass)
        {
            os << "mass: " << mass._mass << std::endl;
            return os;
        }
    };

    struct Paralax {
        float _paralax;

        friend std::ostream &operator<<(std::ostream &os, const Paralax &paralax)
        {
            os << "paralax: " << paralax._paralax << std::endl;
            return os;
        }
    };

    struct OutlineBox2D {
        float _width;
        float _height;

        OutlineBox2D(float width = 0, float height = 0) : _width(width), _height(height)
        {
            _outline.setSize(sf::Vector2f(width, height));
            _outline.setFillColor(sf::Color::Transparent);
            _outline.setOutlineColor(sf::Color::Red);
            _outline.setOutlineThickness(5);
        }

        friend std::ostream &operator<<(std::ostream &os, const OutlineBox2D &outlineBox)
        {
            os << "outline box: " << std::endl;
            os << "\tsize: { " << outlineBox._width << ", " << outlineBox._height << " }" << std::endl;
            return os;
        }

        sf::RectangleShape _outline;
    };

    struct ColisionBoxCustom {
        float _offsetx;
        float _offsety;
        float _offsetz;

        float _width;
        float _height;
        float _depth;

        bool _isTrigger;

        enum Layer {
            PLAYER = 0,
            MISSILE = 1,
            ENEMY = 2,
            OBSTACLE = 3,
        };

        Layer _layer;

        std::vector<std::vector<bool>> _layersMatrix;

        friend std::ostream &operator<<(std::ostream &os, const ColisionBoxCustom &colisionBox)
        {
            os << "colision box: " << std::endl;
            os << "\tpos: { " << colisionBox._offsetx << ", " << colisionBox._offsety << ", " << colisionBox._offsetz << " }" << std::endl;
            os << "\tsize: { " << colisionBox._width << ", " << colisionBox._height << ", " << colisionBox._depth << " }" << std::endl;
            os << "\tisTrigger: " << colisionBox._isTrigger << std::endl;
            os << "\tlayer: " << colisionBox._layer << std::endl;
            os << "\tlayersMatrix: " << std::endl;
            for (auto const &layer : colisionBox._layersMatrix) {
                for (auto const &layer2 : layer) {
                    os << layer2 << " ";
                }
                os << std::endl;
            }
            return os;
        }
    };

    struct Bullet {
        float _damage;

        friend std::ostream &operator<<(std::ostream &os, const Bullet &bullet)
        {
            os << "bullet: " << std::endl;
            os << "\tdamage: " << bullet._damage << std::endl;
            return os;
        }
    };

    struct Health {
        float _health;

        friend std::ostream &operator<<(std::ostream &os, const Health &health)
        {
            os << "health: " << std::endl;
            os << "\thealth: " << health._health << std::endl;
            return os;
        }
    };

    struct Id {
        size_t _id;
    };

    struct IsEnemy {
    };

    struct hasTouch {
        bool _hasTouch = false;
    };

}
