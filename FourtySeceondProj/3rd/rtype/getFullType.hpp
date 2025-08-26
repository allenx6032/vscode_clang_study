/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include <cstdlib>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

/**
 * @brief Get the full type name of a variable
 *
 * @tparam T The type of the variable
 * @return std::string The full type name of the variable
 * @note How to use:
 * @code typeName<decltype(VAR_TO_CHECK_NOT_TYPE_ITSELF)>()
 */
template <class T>
std::string typeName() {
    typedef typename std::remove_reference<T>::type TR;

    #ifndef _MSC_VER
        std::unique_ptr<char, void (*)(void *)> own(abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr), std::free);
    #else
        std::unique_ptr<char, void (*)(void *)> own(nullptr, std::free);
    #endif

    std::string r = own != nullptr ? own.get() : typeid(TR).name();

    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}
