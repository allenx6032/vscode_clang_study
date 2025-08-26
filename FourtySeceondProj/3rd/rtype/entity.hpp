/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "components.hpp"
#include <any>
#include <vector>

class Entity {
    public:
        Entity() = delete;
        ~Entity()
        {
        };

        // make the entity convertible to a size_t
        operator std::size_t() const { return m_size; }

        friend class Registry;

    private:
        // private constructor, only a registry can create entities (so that we can keep track of them) (make the registry a friend class)
        Entity(std::size_t size) : m_size(size)
        {
        };

        std::size_t m_size;

        // std::vector<std::any> components;
};
