/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include <cassert>

namespace gameEngine {
    namespace priv {
        constexpr float pi = 3.141592654f;

        constexpr float positiveRemainder(float a, float b)
        {
            assert(b > 0.0f && "Cannot calculate remainder with non-positive divisor");
            const float val = a - static_cast<float>(static_cast<int>(a / b)) * b;
            if (val >= 0.f)
                return val;
            else
                return val + b;
        }
    }

    class Angle {
        public:
            constexpr Angle() = default;

            [[nodiscard]] constexpr float asDegrees() const;
            [[nodiscard]] constexpr float asRadians() const;

            [[nodiscard]] constexpr Angle wrapSigned() const;
            [[nodiscard]] constexpr Angle wrapUnsigned() const;

            static const Angle Zero;

        public:
            constexpr Angle(float degrees);
            // Angle(const sf::Angle& angle) : m_degrees(angle.asDegrees()) {};

            operator float() const { return asDegrees(); }
            // operator sf::Angle() const { return sf::Angle(asDegrees()); }

        private:
            friend constexpr Angle degrees(float angle);
            friend constexpr Angle radians(float angle);

            float m_degrees{};
    };

    [[nodiscard]] constexpr Angle degrees(float angle) { return Angle(angle); };

    [[nodiscard]] constexpr Angle radians(float angle) { return Angle(angle * (180 / priv::pi)); };

    constexpr float Angle::asDegrees() const { return m_degrees; };
    constexpr float Angle::asRadians() const { return m_degrees * (priv::pi / 180); };
    constexpr Angle Angle::wrapSigned() const { return degrees(priv::positiveRemainder(m_degrees + 180, 360) - 180); };
    constexpr Angle Angle::wrapUnsigned() const { return degrees(priv::positiveRemainder(m_degrees, 360)); };
    constexpr Angle::Angle(float degrees) : m_degrees(degrees) {};

    [[nodiscard]] constexpr bool operator==(Angle left, Angle right) { return left.asDegrees() == right.asDegrees(); };

    [[nodiscard]] constexpr bool operator!=(Angle left, Angle right) { return left.asDegrees() != right.asDegrees(); };

    [[nodiscard]] constexpr bool operator<(Angle left, Angle right) { return left.asDegrees() < right.asDegrees(); };

    [[nodiscard]] constexpr bool operator>(Angle left, Angle right) { return left.asDegrees() > right.asDegrees(); };

    [[nodiscard]] constexpr bool operator<=(Angle left, Angle right) { return left.asDegrees() <= right.asDegrees(); };

    [[nodiscard]] constexpr bool operator>=(Angle left, Angle right) { return left.asDegrees() >= right.asDegrees(); };

    [[nodiscard]] constexpr Angle operator-(Angle right) { return degrees(-right.asDegrees()); };

    [[nodiscard]] constexpr Angle operator+(Angle left, Angle right) { return degrees(left.asDegrees() + right.asDegrees()); };

    constexpr Angle& operator+=(Angle& left, Angle right) { return left = left + right; };

    [[nodiscard]] constexpr Angle operator-(Angle left, Angle right) { return degrees(left.asDegrees() - right.asDegrees()); };

    constexpr Angle& operator-=(Angle& left, Angle right) { return left = left - right; };

    [[nodiscard]] constexpr Angle operator*(Angle left, float right) { return degrees(left.asDegrees() * right); };

    [[nodiscard]] constexpr Angle operator*(float left, Angle right) { return degrees(left * right.asDegrees()); };

    constexpr Angle& operator*=(Angle& left, float right) { return left = left * right; };

    [[nodiscard]] constexpr Angle operator/(Angle left, float right) { return degrees(left.asDegrees() / right); };

    constexpr Angle& operator/=(Angle& left, float right) { return left = left / right; };

    [[nodiscard]] constexpr float operator/(Angle left, Angle right) { return left.asDegrees() / right.asDegrees(); };

    [[nodiscard]] constexpr Angle operator%(Angle left, Angle right) { return degrees(priv::positiveRemainder(left.asDegrees(), right.asDegrees())); };

    constexpr Angle& operator%=(Angle& left, Angle right) { return left = left % right; };

    namespace Literals
    {
        [[nodiscard]] constexpr Angle operator""_deg(long double angle) { return degrees(static_cast<float>(angle)); };

        [[nodiscard]] constexpr Angle operator""_deg(unsigned long long int angle) { return degrees(static_cast<float>(angle)); };

        [[nodiscard]] constexpr Angle operator""_rad(long double angle) { return radians(static_cast<float>(angle)); };

        [[nodiscard]] constexpr Angle operator""_rad(unsigned long long int angle) { return radians(static_cast<float>(angle)); };
    }

    inline constexpr Angle Angle::Zero;
}
