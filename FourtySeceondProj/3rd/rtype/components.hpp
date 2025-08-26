/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "GraphicLib.hpp"
#include <sfml/SFML_Graphics.hpp>
#include <iostream>

#define MAX_RGBA_VALUE 255

namespace component {
    // create a transform component
    struct Transform {
        float _posx;
        float _posy;
        float _posz;

        float _rotx;
        float _roty;
        float _rotz;

        float _scalex;
        float _scaley;
        float _scalez;

        friend std::ostream &operator<<(std::ostream &os, const Transform &transform)
        {
            os << "pos: { " << transform._posx << ", " << transform._posy << ", " << transform._posz << " }" << std::endl;
            os << "rot: { " << transform._rotx << ", " << transform._roty << ", " << transform._rotz << " }" << std::endl;
            os << "scale: { " << transform._scalex << ", " << transform._scaley << ", " << transform._scalez << " }" << std::endl;
            return os;
        }
    };

    // create a velocity component
    struct Velocity {
        float _velx;
        float _vely;
        float _velz;

        friend std::ostream &operator<<(std::ostream &os, const Velocity &velocity)
        {
            os << "vel: { " << velocity._velx << ", " << velocity._vely << ", " << velocity._velz << " }" << std::endl;
            return os;
        }
    };

    // create a drawable component
    struct Drawable {
        bool _isDrawable;

        friend std::ostream &operator<<(std::ostream &os, const Drawable &drawable)
        {
            os << "is drawable: " << drawable._isDrawable << std::endl;
            return os;
        }
    };

    // create a crontrollable component
    struct Controllable {
        bool _isControllable;

        friend std::ostream &operator<<(std::ostream &os, const Controllable &controllable)
        {
            os << "is controllable: " << controllable._isControllable << std::endl;
            return os;
        }
    };

    // create a texture component
    struct Texture {
        sf::Texture _texture;

        float _offsetX;
        float _offsetY;

        Texture(sf::Uint8 r = MAX_RGBA_VALUE, sf::Uint8 g = MAX_RGBA_VALUE, sf::Uint8 b = MAX_RGBA_VALUE, sf::Uint8 a = MAX_RGBA_VALUE) {
            sf::Image img;
            img.create(1, 1, sf::Color(r, g, b, a));
            this->_texture.loadFromImage(img);
        }

        Texture(const std::string &path) { this->_texture.loadFromFile(path); }

        friend std::ostream &operator<<(std::ostream &os, const Texture &texture)
        {
            os << "texture: { " << texture._texture.getSize().x << ", " << texture._texture.getSize().y << " }" << std::endl;
            return os;
        }
    };

    // create a sprite component
    struct Sprite {
        sf::Sprite _sprite;
        sf::IntRect _rect;

        Sprite(sf::IntRect _rect = sf::IntRect(0, 0, 0, 0)) {
            this->_rect = _rect;
            this->_sprite.setTextureRect(this->_rect);
        }

        friend std::ostream &operator<<(std::ostream &os, const Sprite &sprite)
        {
            os << "sprite pos: { " << sprite._sprite.getPosition().x << ", " << sprite._sprite.getPosition().y << " }" << std::endl;
            os << "sprite scale: { " << sprite._sprite.getScale().x << ", " << sprite._sprite.getScale().y << " }" << std::endl;
            os << "sprite rect: { " << sprite._rect.left << ", " << sprite._rect.top << ", " << sprite._rect.width << ", " << sprite._rect.height << " }" << std::endl;
            return os;
        }
    };

    // create a animation component
    struct Animation {
        std::string _jsonPath;
        gameEngine::Clock _clock;
        gameEngine::Time _time;
        int _currentFrame;
        bool _isLooping;
        bool _automaticAnimation;
        bool _checked = false;

        Animation(const std::string &_jsonPath = "", gameEngine::Time _time = gameEngine::Time::Zero, bool _isLooping = false, bool _automaticAnimation = true)
        {
            this->_jsonPath = _jsonPath;
            this->_time = _time;
            this->_isLooping = _isLooping;
            this->_currentFrame = 0;
            this->_automaticAnimation = _automaticAnimation;
            this->_clock.restart();
        }

        friend std::ostream &operator<<(std::ostream &os, const Animation &animation)
        {
            os << "json path: " << animation._jsonPath << std::endl;
            os << "time: " << animation._time.asSeconds() << std::endl;
            os << "is looping: " << animation._isLooping << std::endl;
            os << "current frame: " << animation._currentFrame << std::endl;
            return os;
        }
    };

    // create a colision box component
    struct ColisionBox {
        float _width;
        float _height;
        float _depth;

        friend std::ostream &operator<<(std::ostream &os, const ColisionBox &colisionBox)
        {
            os << "colision box: { " << colisionBox._width << ", " << colisionBox._height << ", " << colisionBox._depth << " }" << std::endl;
            return os;
        }
    };

    // create a unmovable component
    struct Unmovable {
        bool _isUnmovable;

        friend std::ostream &operator<<(std::ostream &os, const Unmovable &unmovable)
        {
            os << "is unmovable: " << unmovable._isUnmovable << std::endl;
            return os;
        }
    };

    struct ToDelete {
        bool _toDelete = true;

        friend std::ostream &operator<<(std::ostream &os, const ToDelete &toDelete)
        {
            os << "to delete: " << toDelete._toDelete << std::endl;
            return os;
        }
    };

    struct EnemyType {
        enum Type {
            SIMPLE,
            OTHER,
            MECHA,
            MISSILE,
            BOSS
        };

        Type _type;

        friend std::ostream &operator<<(std::ostream &os, const EnemyType &enemyType)
        {
            os << "type: " << enemyType._type << std::endl;
            return os;
        }
    };
}
