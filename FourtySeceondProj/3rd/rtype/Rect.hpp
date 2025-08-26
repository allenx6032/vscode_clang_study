/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Vector2.hpp"
#include <sfml/SFML_Rect.hpp>
#include <optional>

namespace gameEngine {
    template <typename T>
    class Rect {
        public:
            constexpr Rect() = default;

            constexpr Rect(const Vector2<T>& position, const Vector2<T>& size) :
                left(position.x),
                top(position.y),
                width(size.x),
                height(size.y)
            {
            };

            constexpr Rect(T left, T top, T width, T height) :
                left(left),
                top(top),
                width(width),
                height(height)
            {
            };

            template <typename U>
            constexpr explicit Rect(const Rect<U>& rectangle) :
                left(static_cast<T>(rectangle.left)),
                top(static_cast<T>(rectangle.top)),
                width(static_cast<T>(rectangle.width)),
                height(static_cast<T>(rectangle.height))
            {
            };

            constexpr bool contains(const Vector2<T>& point) const
            {
                // Not using 'std::min' and 'std::max' to avoid depending on '<algorithm>'
                const auto min = [](T a, T b) { return (a < b) ? a : b; };
                const auto max = [](T a, T b) { return (a < b) ? b : a; };

                // Rectangles with negative dimensions are allowed, so we must handle them correctly

                // Compute the real min and max of the rectangle on both axes
                const T minX = min(left, static_cast<T>(left + width));
                const T maxX = max(left, static_cast<T>(left + width));
                const T minY = min(top, static_cast<T>(top + height));
                const T maxY = max(top, static_cast<T>(top + height));

                return (point.x >= minX) && (point.x < maxX) && (point.y >= minY) && (point.y < maxY);
            };

            constexpr bool contains(const T& x, const T& y) const
            {
                return contains(Vector2<T>(x, y));
            };

            constexpr std::optional<Rect<T>> findIntersection(const Rect<T>& rectangle) const
            {
                // Not using 'std::min' and 'std::max' to avoid depending on '<algorithm>'
                const auto min = [](T a, T b) { return (a < b) ? a : b; };
                const auto max = [](T a, T b) { return (a < b) ? b : a; };

                // Rectangles with negative dimensions are allowed, so we must handle them correctly

                // Compute the min and max of the first rectangle on both axes
                const T r1MinX = min(left, static_cast<T>(left + width));
                const T r1MaxX = max(left, static_cast<T>(left + width));
                const T r1MinY = min(top, static_cast<T>(top + height));
                const T r1MaxY = max(top, static_cast<T>(top + height));

                // Compute the min and max of the second rectangle on both axes
                const T r2MinX = min(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
                const T r2MaxX = max(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
                const T r2MinY = min(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));
                const T r2MaxY = max(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));

                // Compute the intersection boundaries
                const T interLeft   = max(r1MinX, r2MinX);
                const T interTop    = max(r1MinY, r2MinY);
                const T interRight  = min(r1MaxX, r2MaxX);
                const T interBottom = min(r1MaxY, r2MaxY);

                // If the intersection is valid (positive non zero area), then there is an intersection
                if ((interLeft < interRight) && (interTop < interBottom))
                {
                    return Rect<T>({interLeft, interTop}, {interRight - interLeft, interBottom - interTop});
                }
                else
                {
                    return std::nullopt;
                }
            };

            constexpr Vector2<T> getPosition() const
            {
                return Vector2<T>(left, top);
            };

            constexpr Vector2<T> getSize() const
            {
                return Vector2<T>(width, height);
            };

            T left;    // <-- Left coordinate of the rectangle
            T top;     // <-- Top coordinate of the rectangle
            T width;   // <-- Width of the rectangle
            T height;  // <-- Height of the rectangle

        public:
            Rect(const sf::Rect<T>& rectangle) :
                left(rectangle.left),
                top(rectangle.top),
                width(rectangle.width),
                height(rectangle.height)
            {
            };

            operator sf::Rect<T>() const
            {
                return sf::Rect<T>(left, top, width, height);
            };
    };

    template <typename T>
    [[nodiscard]] constexpr bool operator==(const Rect<T>& left, const Rect<T>& right)
    {
        return (left.left == right.left) &&
                (left.top == right.top) &&
                (left.width == right.width) &&
                (left.height == right.height);
    };

    template <typename T>
    [[nodiscard]] constexpr bool operator!=(const Rect<T>& left, const Rect<T>& right)
    {
        return !(left == right);
    };

    using IntRect   = Rect<int>;
    using FloatRect = Rect<float>;
}