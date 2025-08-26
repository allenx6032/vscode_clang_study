/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include <rtype/getFullType.hpp>
#include <iostream>
#include <sfml/SFML_Vector3.hpp>

namespace gameEngine {
    template <typename T>
    class Vector3 {
        public:
            Vector3() : x(0), y(0), z(0)
            {
            };

            Vector3(T x, T y, T z) : x(x), y(y), z(z)
            {
            };

            template <typename U>
            explicit Vector3(const Vector3<U>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z))
            {
            };

            T x; // <-- X coordinate of the vector
            T y; // <-- Y coordinate of the vector
            T z; // <-- Z coordinate of the vector

        public:
            Vector3(const sf::Vector3<T>& vector) : x(vector.x), y(vector.y), z(vector.z)
            {
            };

            operator sf::Vector3<T>() const
            {
                return sf::Vector3<T>(x, y, z);
            };
    };

    typedef Vector3<int>          Vector3i;
    typedef Vector3<unsigned int> Vector3u;
    typedef Vector3<float>        Vector3f;

    // INFO: Unary operators
    template <typename T>
    Vector3<T> operator -(const Vector3<T>& right)
    {
        return Vector3<T>(-right.x, -right.y, -right.z);
    }

    // INFO: Add
    template <typename T>
    Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right)
    {
        return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
    }

    template <typename T>
    Vector3<T>& operator +=(Vector3<T>& left, const Vector3<T>& right)
    {
        left.x += right.x;
        left.y += right.y;
        left.z += right.z;
        return left;
    }

    // INFO: Sub
    template <typename T>
    Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right)
    {
        return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
    }

    template <typename T>
    Vector3<T>& operator -=(Vector3<T>& left, const Vector3<T>& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        left.z -= right.z;
        return left;
    }

    // INFO: Multiply
    template <typename T>
    Vector3<T> operator *(const Vector3<T>& left, T right)
    {
        return Vector3<T>(left.x * right, left.y * right, left.z * right);
    }

    template <typename T>
    Vector3<T> operator *(T left, const Vector3<T>& right)
    {
        return Vector3<T>(right.x * left, right.y * left, right.z * left);
    }

    template <typename T>
    Vector3<T>& operator *=(Vector3<T>& left, T right)
    {
        left.x *= right;
        left.y *= right;
        left.z *= right;
        return left;
    }

    // INFO: Divide
    template <typename T>
    Vector3<T> operator /(const Vector3<T>& left, T right)
    {
        return Vector3<T>(left.x / right, left.y / right, left.z / right);
    }

    template <typename T>
    Vector3<T>& operator /=(Vector3<T>& left, T right)
    {
        left.x /= right;
        left.y /= right;
        left.z /= right;
        return left;
    }

    // INFO: Equality
    template <typename T>
    bool operator ==(const Vector3<T>& left, const Vector3<T>& right)
    {
        return (left.x == right.x && left.y == right.y && left.z == right.z);
    }

    template <typename T>
    bool operator !=(const Vector3<T>& left, const Vector3<T>& right)
    {
        return !(left == right);
    }

    // INFO: Stream
    template <typename T>
    std::ostream& operator <<(std::ostream& os, const Vector3<T>& vector)
    {
        os << "Vector3<" << typeName<decltype(vector.x)>() << ">(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
        return os;
    }
}
