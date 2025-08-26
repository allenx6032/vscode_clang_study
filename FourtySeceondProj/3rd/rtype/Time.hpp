/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Config.hpp"
#include <sfml/SFML_Time.hpp>

namespace gameEngine {
    class Time {
        public:
            Time() :
                _time()
            {
            };

            float asSeconds() const { return _time.asSeconds(); };
            Int32 asMilliseconds() const { return _time.asMilliseconds(); };
            Int64 asMicroseconds() const { return _time.asMicroseconds(); };

            static const Time Zero;

        public:
            Time(const sf::Time &time) :
                _time(time)
            {
            };

            operator sf::Time() const { return _time; };

        private:
            sf::Time _time;
    };

    inline const Time Time::Zero;
}
