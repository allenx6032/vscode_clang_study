/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "lua/lua.hpp"
#include "exception.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#define LUA_TABLE_MAP_TYPE std::map<std::string, std::variant<std::string, int, float, double, bool>>
#define LUA_TABLE_VECTOR_TYPE std::vector<std::variant<std::string, int, float, double, bool>>

class LuaManager {
    public:
        LuaManager() = default;
        ~LuaManager()
        {
            for (auto &luaState : _luaStates)
                lua_close(luaState.second);
        };

    public:
        /**
         * @brief Load a lua file
         *
         * @param path The path to the lua file
         *
         * @throw gameEngine::lua::InvalidLuaFile If the file does not exist or is not a lua file
         */
        void luaLoadFile(const std::string &path);

        /**
         * @brief Add C++ function to lua so it can be called from lua
         *
         * @param fromFile The file where the function will be added
         * @param name The name of the function
         * @param func The function
         *
         * @throw gameEngine::lua::InvalidLuaFunction If the function name is invalid
         */
        void luaAddCppFunction(const std::string &fromFile, const std::string &name, lua_CFunction func);

        /**
         * @brief Call a lua function
         *
         * @param fromFile The file where the function is
         * @param name The name of the function
         * @param nbReturnValue The number of return value
         * @param args The arguments to pass to the function
         *
         * @throw gameEngine::lua::InvalidLuaFunction If the function does not exist
         * @throw gameEngine::lua::InvalidLuaType If an argument does not have a valid type
         */
        template <typename... Args>
        void luaCallFunction(const std::string &fromFile, const std::string &name, int nbReturnValue, Args... args)
        {
            if (_luaStates.find(fromFile) == _luaStates.end())
                throw gameEngine::lua::InvalidLuaFile("File '" + fromFile + "' does not exist");
            lua_getglobal(_luaStates[fromFile], name.c_str());
            if (!lua_isfunction(_luaStates[fromFile], -1))
                throw gameEngine::lua::InvalidLuaFunction("Function '" + name + "' does not exist");

            size_t nbArgs = sizeof...(args);
            (luaPushValueToStack(_luaStates[fromFile], args), ...);

            if (lua_pcall(_luaStates[fromFile], nbArgs, nbReturnValue, 0) != 0)
                luaL_error(_luaStates[fromFile], "Error while calling lua function '%s': %s", name.c_str(), lua_tostring(_luaStates[fromFile], -1));
        };

        /**
         * @brief Get return value of the last function call
         *
         * @param fromFile The file on which the function was called
         * @param args References to each return value
         *
         * @throw gameEngine::lua::InvalidLuaType If an argument does not have a valid type
         */
        template <typename... Args>
        void luaGetReturnValue(const std::string &fromFile, Args&... args)
        {
            if (_luaStates.find(fromFile) == _luaStates.end())
                throw gameEngine::lua::InvalidLuaFile("File '" + fromFile + "' does not exist");

            size_t nbArgs = sizeof...(args);
            (luaGetValueFromStack(_luaStates[fromFile], args, nbArgs--), ...);
        };

        /**
         * @brief Get arguments from the lua stack
         *
         * @param args References to each argument to get
         *
         * @throw gameEngine::lua::InvalidLuaType If an argument does not have a valid type
         */
        template <typename... Args>
        static void luaGetArgument(lua_State *luaState, Args&... args)
        {
            size_t nbArgs = sizeof...(args);
            (luaGetValueFromStack(luaState, args, nbArgs--), ...);
        };

        /**
         * @brief Send result to the lua stack
         *
         * @param args References to each argument to send
         *
         * @throw gameEngine::lua::InvalidLuaType If an argument does not have a valid type
         */
        template <typename... Args>
        static void luaSendResult(lua_State *luaState, Args&... args)
        {
            (luaPushValueToStack(luaState, args), ...);
        };

        /**
         * @brief Debug function to print the lua stack
         *
         * @param fromFile The file of the stack to print
         */
        void luaPrintStack(const std::string &fromFile);

    // INFO: Get Lua Value
    private:
        /**
         * @brief Get a value from the lua stack
         *
         * @param returnValue Reference to the return value
         * @param nbArgs The number of the argument on the stack
         */
        static void luaGetValueFromStack(lua_State *luaState, std::string &returnValue, size_t nbArgs);
        static void luaGetValueFromStack(lua_State *luaState, int &returnValue, size_t nbArgs);
        static void luaGetValueFromStack(lua_State *luaState, float &returnValue, size_t nbArgs);
        static void luaGetValueFromStack(lua_State *luaState, double &returnValue, size_t nbArgs);
        static void luaGetValueFromStack(lua_State *luaState, bool &returnValue, size_t nbArgs);
        static void luaGetValueFromStack(lua_State *luaState, LUA_TABLE_MAP_TYPE &returnValue, size_t nbArgs);
        static void luaGetValueFromStack(lua_State *luaState, LUA_TABLE_VECTOR_TYPE &returnValue, size_t nbArgs);

        template <typename T>
        static void luaGetValueFromStack(lua_State *luaState, T &returnValue, size_t nbArgs)
        {
            throw gameEngine::lua::InvalidLuaType("Invalid/Unsupported return type");
        };

    // INFO: Pushing to stack functions
    private:
        /**
         * @brief Add an argument to the lua stack
         *
         * @param arg The argument to add
         */
        static void luaPushValueToStack(lua_State *luaState, const std::string &arg);
        static void luaPushValueToStack(lua_State *luaState, const int &arg);
        static void luaPushValueToStack(lua_State *luaState, const float &arg);
        static void luaPushValueToStack(lua_State *luaState, const double &arg);
        static void luaPushValueToStack(lua_State *luaState, const bool &arg);
        static void luaPushValueToStack(lua_State *luaState, const LUA_TABLE_MAP_TYPE &arg);
        static void luaPushValueToStack(lua_State *luaState, const LUA_TABLE_VECTOR_TYPE &arg);

        template <typename T>
        static void luaPushValueToStack(lua_State *luaState, const T &arg)
        {
            throw gameEngine::lua::InvalidLuaType("Invalid/Unsupported argument type");
        };

    private:
        std::unordered_map<std::string, lua_State *> _luaStates;
};
