/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Time.hpp"
#include <sfml/SFML_Clock.hpp>

namespace gameEngine {
    class Clock {
        public:
            Clock() :
                _clock()
            {
            };

            void restart() { _clock.restart(); };
            Time getElapsedTime() const {
                sf::Time time = _clock.getElapsedTime();
                return Time(time);
            };

        private:
            sf::Clock _clock;
    };
}
