/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include <rtype/getFullType.hpp>
#include <iostream>
#include <sfml/SFML_Vector2.hpp>

namespace gameEngine {
    template <typename T>
    class Vector2 {
        public:
            Vector2() : x(0), y(0)
            {
            };

            Vector2(T x, T y) : x(x), y(y)
            {
            };

            template <typename U>
            explicit Vector2(const Vector2<U>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y))
            {
            };

            T x; // <-- X coordinate of the vector
            T y; // <-- Y coordinate of the vector

        public:
            Vector2(const sf::Vector2<T>& vector) : x(vector.x), y(vector.y)
            {
            };

            operator sf::Vector2<T>() const
            {
                return sf::Vector2<T>(x, y);
            };
    };

    typedef Vector2<int>          Vector2i;
    typedef Vector2<unsigned int> Vector2u;
    typedef Vector2<float>        Vector2f;

    // INFO: Unary operators
    template <typename T>
    Vector2<T> operator -(const Vector2<T>& right)
    {
        return Vector2<T>(-right.x, -right.y);
    }

    // INFO: Add
    template <typename T>
    Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right)
    {
        return Vector2<T>(left.x + right.x, left.y + right.y);
    }

    template <typename T>
    Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right)
    {
        left.x += right.x;
        left.y += right.y;
        return left;
    }

    // INFO: Sub
    template <typename T>
    Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right)
    {
        return Vector2<T>(left.x - right.x, left.y - right.y);
    }

    template <typename T>
    Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        return left;
    }

    // INFO: Multiply
    template <typename T>
    Vector2<T> operator *(const Vector2<T>& left, T right)
    {
        return Vector2<T>(left.x * right, left.y * right);
    }

    template <typename T>
    Vector2<T> operator *(T left, const Vector2<T>& right)
    {
        return Vector2<T>(right.x * left, right.y * left);
    }

    template <typename T>
    Vector2<T>& operator *=(Vector2<T>& left, T right)
    {
        left.x *= right;
        left.y *= right;
        return left;
    }

    // INFO: Divide
    template <typename T>
    Vector2<T> operator /(const Vector2<T>& left, T right)
    {
        return Vector2<T>(left.x / right, left.y / right);
    }

    template <typename T>
    Vector2<T>& operator /=(Vector2<T>& left, T right)
    {
        left.x /= right;
        left.y /= right;
        return left;
    }

    // INFO: Equal
    template <typename T>
    bool operator ==(const Vector2<T>& left, const Vector2<T>& right)
    {
        return (left.x == right.x && left.y == right.y);
    }

    template <typename T>
    bool operator !=(const Vector2<T>& left, const Vector2<T>& right)
    {
        return !(left == right);
    }

    // INFO: Stream
    template <typename T>
    std::ostream& operator <<(std::ostream& os, const Vector2<T>& vector)
    {
        os << "Vector2<" << typeName<decltype(vector.x)>() << ">(" << vector.x << ", " << vector.y << ")";
        return os;
    }
}
