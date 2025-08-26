/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Vector2.hpp"
#include <sfml/SFML_Mouse.hpp>

namespace gameEngine {
    class RenderWindow;

    class Mouse {
        public:
            enum Button {
                Left,               // <-- The left mouse button
                Right,              // <-- The right mouse button
                Middle,             // <-- The middle (wheel) mouse button
                XButton1,           // <-- The first extra mouse button
                XButton2,           // <-- The second extra mouse button

                ButtonCount         // <-- Keep last -- the total number of mouse buttons
            };

            enum Wheel {
                VerticalWheel,      // <-- The mouse wheel
                HorizontalWheel     // <-- The mouse wheel
            };

            /**
             * @brief Check if a mouse button is pressed
             *
             * @param button Button to check
             * @return true If the button is pressed
             * @return false If the button is not pressed
             */
            static bool isButtonPressed(Button button);

            /**
             * @brief Get the current position of the mouse in desktop coordinates
             *
             * This function returns the global position of the mouse
             * cursor on the desktop.
             *
             * @return Vector2i Current position of the mouse
             */
            static Vector2i getPosition();

            /**
             * @brief Get the current position of the mouse in window coordinates
             *
             * This function returns the current position of the mouse
             * cursor, relative to the given window.
             *
             * @param relativeTo Reference window
             * @return Vector2i Current position of the mouse
             */
            static Vector2i getPosition(RenderWindow& relativeTo);

            /**
             * @brief Set the current position of the mouse in desktop coordinates
             *
             * This function sets the global position of the mouse
             * cursor on the desktop.
             *
             * @param position New position of the mouse
             */
            static void setPosition(const Vector2i& position);

            /**
             * @brief Set the current position of the mouse in window coordinates
             *
             * This function sets the current position of the mouse
             * cursor, relative to the given window.
             *
             * @param position New position of the mouse
             * @param relativeTo Reference window
             */
            static void setPosition(const Vector2i& position, RenderWindow& relativeTo);
    };
}
