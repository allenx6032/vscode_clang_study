/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include <map>
#include <memory>
#include <vector>

template <typename Component> // You can also mirror the definition of std :: vector , that takes an additional allocator .
class SparseArray
{
    public:
        using value_type = Component; // optional component type

        using reference_type = value_type &;
        using const_reference_type = value_type const &;

        using container_t = std::map<std::size_t, value_type>; // optionally add your allocator

        using size_type = typename container_t::size_type;

        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

    public:
        SparseArray();                        // You can add more constructors
        SparseArray(SparseArray const &);     // copy constructor
        SparseArray(SparseArray &&) noexcept; // move constructor

        ~SparseArray();

        SparseArray &operator=(SparseArray const &);     // copy assignment operator
        SparseArray &operator=(SparseArray &&) noexcept; // move assignment operator

        /**
         * @brief Get a reference to a component at a given index
         *
         * @param idx The index of the component
         * @return reference_type A reference to the component
        **/
        reference_type operator[](std::size_t idx);
        /**
         * @brief Get a const reference to a component at a given index
         *
         * @param idx The index of the component
         * @return const_reference_type A const reference to the component
        **/
        const_reference_type operator[](std::size_t idx) const;

        /**
         * @brief Get an iterator to the beginning of the sparse array
         *
         * @return iterator An iterator to the beginning of the sparse array
        **/
        iterator begin();
        /**
         * @brief Get a const iterator to the beginning of the sparse array
         *
         * @return const_iterator A const iterator to the beginning of the sparse array
        **/
        const_iterator begin() const;
        /**
         * @brief Get a const iterator to the beginning of the sparse array
         *
         * @return const_iterator A const iterator to the beginning of the sparse array
         * @note This is the same as begin()
        **/
        const_iterator cbegin() const;

        /**
         * @brief Get an iterator to the end of the sparse array
         *
         * @return iterator An iterator to the end of the sparse array
        **/
        iterator end();
        /**
         * @brief Get a const iterator to the end of the sparse array
         *
         * @return const_iterator A const iterator to the end of the sparse array
        **/
        const_iterator end() const;
        /**
         * @brief Get a const iterator to the end of the sparse array
         *
         * @return const_iterator A const iterator to the end of the sparse array
         * @note This is the same as end()
        **/
        const_iterator cend() const;

        /**
         * @brief Get the size of the sparse array
         *
         * @return size_type The size of the sparse array
         * @note The size of the sparse array is the number of components
         * it contains (not the number of elements in the underlying container)
        **/
        size_type size() const;

        /**
         * @brief Insert a component at a given position
         *
         * @param pos The position where to insert the component
         * @param component The component to insert
         * @return A reference to the inserted component
        **/
        reference_type insertAt(size_type pos, Component const &);
        /**
         * @brief Insert a component at a given position
         *
         * @param pos The position where to insert the component
         * @param component The component to insert
         * @return A reference to the inserted component
         * @note The component is moved
        **/
        reference_type insertAt(size_type pos, Component &&);

        /**
         * @brief Construct a new Component object at a given position
         * with the given parameters and return a reference to it
         *
         * @tparam Params The types of the parameters
         * @param pos The position where to insert the component
         * @param params The parameters to construct the component
         * @return reference_type A reference to the inserted component
        **/
        template <class... Params>
        reference_type emplaceAt(size_type pos, Params &&...); // optional

        /**
         * @brief Erase a component at a given position
         *
         * @param pos The position of the component to erase
        **/
        void erase(size_type pos);

        /**
         * @brief Get the index of a component
         *
         * @param component The component to get the index of
         * @return size_type The index of the component
        **/
        size_type getIndex(value_type const &) const;

        /**
         * @brief Check if a component exists at a given position
         *
         * @param pos The position to check
         * @return true If a component exists at the given position
         * @return false If no component exists at the given position
        **/
        bool has(size_type pos) const;

    private:
        container_t _data;
};

template <typename Component>
SparseArray<Component>::SparseArray() : _data()
{
}

template <typename Component>
SparseArray<Component>::SparseArray(SparseArray const &other) : _data(other._data)
{
}

template <typename Component>
SparseArray<Component>::SparseArray(SparseArray &&other) noexcept : _data(std::move(other._data))
{
}

template <typename Component>
SparseArray<Component>::~SparseArray()
{
}

template <typename Component>
SparseArray<Component> &SparseArray<Component>::operator=(SparseArray const &other)
{
    if (this != &other)
    {
        _data = other._data;
    }
    return *this;
}

template <typename Component>
SparseArray<Component> &SparseArray<Component>::operator=(SparseArray &&other) noexcept
{
    if (this != &other)
    {
        _data = std::move(other._data);
    }
    return *this;
}

template <typename Component>
typename SparseArray<Component>::reference_type SparseArray<Component>::operator[](std::size_t idx)
{
    return _data[idx];
}

template <typename Component>
typename SparseArray<Component>::const_reference_type SparseArray<Component>::operator[](std::size_t idx) const
{
    return _data[idx];
}

template <typename Component>
typename SparseArray<Component>::iterator SparseArray<Component>::begin()
{
    return _data.begin();
}

template <typename Component>
typename SparseArray<Component>::const_iterator SparseArray<Component>::begin() const
{
    return _data.begin();
}

template <typename Component>
typename SparseArray<Component>::const_iterator SparseArray<Component>::cbegin() const
{
    return _data.cbegin();
}

template <typename Component>
typename SparseArray<Component>::iterator SparseArray<Component>::end()
{
    return _data.end();
}

template <typename Component>
typename SparseArray<Component>::const_iterator SparseArray<Component>::end() const
{
    return _data.end();
}

template <typename Component>
typename SparseArray<Component>::const_iterator SparseArray<Component>::cend() const
{
    return _data.cend();
}

template <typename Component>
typename SparseArray<Component>::size_type SparseArray<Component>::size() const
{
    return _data.size();
}

template <typename Component>
typename SparseArray<Component>::reference_type SparseArray<Component>::insertAt(size_type pos, Component const &component)
{
    // _data.insert(_data.begin() + pos, component);
    _data.insert(std::pair<size_t, Component>(pos, component));
    return _data[pos];
}

template <typename Component>
typename SparseArray<Component>::reference_type SparseArray<Component>::insertAt(size_type pos, Component &&component)
{
    // _data.insert(_data.begin() + pos, std::move(component));
    _data.insert(std::pair<size_t, Component>(pos, std::move(component)));
    return _data[pos];
}

template <typename Component>
template <class... Params>
typename SparseArray<Component>::reference_type SparseArray<Component>::emplaceAt(size_type pos, Params &&...params)
{
    // _data.emplace(_data.begin() + pos, std::forward<Params>(params)...);
    _data.emplace(std::pair<size_t, Component>(pos, std::forward<Params>(params)...));
    return _data[pos];
}

template <typename Component>
void SparseArray<Component>::erase(size_type pos)
{
    _data.erase(pos);
}

template <typename Component>
typename SparseArray<Component>::size_type SparseArray<Component>::getIndex(value_type const &component) const
{
    for (size_t i = 0; i < _data.size(); i++)
    {
        if (std::addressof(_data[i]) == std::addressof(component))
        {
            return i;
        }
    }
}

template <typename Component>
bool SparseArray<Component>::has(size_type pos) const
{
    return _data.find(pos) != _data.end();
}
