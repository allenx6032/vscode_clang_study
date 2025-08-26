/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Config.hpp"
#include <sfml/SFML_Color.hpp>

#define MAX_RGBA_VALUE 255

namespace gameEngine {
    class Color {
        public:
            Color() :
                r(0),
                g(0),
                b(0),
                a(MAX_RGBA_VALUE)
            {
            };

            Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = MAX_RGBA_VALUE) :
                r(r),
                g(g),
                b(b),
                a(a)
            {
            };

            Color(const Color& color) :
                r(color.r),
                g(color.g),
                b(color.b),
                a(color.a)
            {
            };

            Color(Uint32 color) :
                r(static_cast<Uint8>((color & 0xFF000000) >> 24)),
                g(static_cast<Uint8>((color & 0x00FF0000) >> 16)),
                b(static_cast<Uint8>((color & 0x0000FF00) >> 8)),
                a(static_cast<Uint8>(color & 0x000000FF))
            {
            };

            Uint8 r; // <-- Red component of the color
            Uint8 g; // <-- Green component of the color
            Uint8 b; // <-- Blue component of the color
            Uint8 a; // <-- Alpha (opacity) component of the color

            static const Color Black;       // <-- Black predefined color
            static const Color White;       // <-- White predefined color
            static const Color Red;         // <-- Red predefined color
            static const Color Green;       // <-- Green predefined color
            static const Color Blue;        // <-- Blue predefined color
            static const Color Yellow;      // <-- Yellow predefined color
            static const Color Magenta;     // <-- Magenta predefined color
            static const Color Cyan;        // <-- Cyan predefined color
            static const Color Transparent; // <-- Transparent (black) predefined color

        public:
            Color(const sf::Color &color) :
                r(color.r),
                g(color.g),
                b(color.b),
                a(color.a)
            {
            };

            operator sf::Color() const { return sf::Color(r, g, b, a); };
    };

    inline const Color Color::Black(0, 0, 0);
    inline const Color Color::White(255, 255, 255);
    inline const Color Color::Red(255, 0, 0);
    inline const Color Color::Green(0, 255, 0);
    inline const Color Color::Blue(0, 0, 255);
    inline const Color Color::Yellow(255, 255, 0);
    inline const Color Color::Magenta(255, 0, 255);
    inline const Color Color::Cyan(0, 255, 255);
    inline const Color Color::Transparent(0, 0, 0, 0);
}