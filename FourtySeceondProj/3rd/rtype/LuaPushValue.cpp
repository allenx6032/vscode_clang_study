/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#include "LuaManager.hpp"

void LuaManager::luaPushValueToStack(lua_State *luaState, const std::string &arg)
{
    lua_pushstring(luaState, arg.c_str());
};

void LuaManager::luaPushValueToStack(lua_State *luaState, const int &arg)
{
    lua_pushinteger(luaState, arg);
};

void LuaManager::luaPushValueToStack(lua_State *luaState, const float &arg)
{
    lua_pushnumber(luaState, arg);
};

void LuaManager::luaPushValueToStack(lua_State *luaState, const double &arg)
{
    lua_pushnumber(luaState, arg);
};

void LuaManager::luaPushValueToStack(lua_State *luaState, const bool &arg)
{
    lua_pushboolean(luaState, arg);
};

void LuaManager::luaPushValueToStack(lua_State *luaState, const LUA_TABLE_MAP_TYPE &arg)
{
    lua_newtable(luaState);
    for (auto &it : arg) {
        lua_pushstring(luaState, it.first.c_str());
        if (std::holds_alternative<std::string>(it.second)) {
            lua_pushstring(luaState, std::get<std::string>(it.second).c_str());
        } else if (std::holds_alternative<int>(it.second)) {
            lua_pushinteger(luaState, std::get<int>(it.second));
        } else if (std::holds_alternative<float>(it.second)) {
            lua_pushnumber(luaState, std::get<float>(it.second));
        } else if (std::holds_alternative<double>(it.second)) {
            lua_pushnumber(luaState, std::get<double>(it.second));
        } else if (std::holds_alternative<bool>(it.second)) {
            lua_pushboolean(luaState, std::get<bool>(it.second));
        } else {
            std::cerr << "Error while pushing lua value '" << it.first.c_str() << "': Invalid type" << std::endl;
            return;
        }
        lua_settable(luaState, -3);
    }
};

void LuaManager::luaPushValueToStack(lua_State *luaState, const LUA_TABLE_VECTOR_TYPE &arg)
{
    lua_newtable(luaState);
    for (size_t i = 0; i < arg.size(); i++) {
        lua_pushinteger(luaState, i + 1);
        if (std::holds_alternative<std::string>(arg[i])) {
            lua_pushstring(luaState, std::get<std::string>(arg[i]).c_str());
        } else if (std::holds_alternative<int>(arg[i])) {
            lua_pushinteger(luaState, std::get<int>(arg[i]));
        } else if (std::holds_alternative<float>(arg[i])) {
            lua_pushnumber(luaState, std::get<float>(arg[i]));
        } else if (std::holds_alternative<double>(arg[i])) {
            lua_pushnumber(luaState, std::get<double>(arg[i]));
        } else if (std::holds_alternative<bool>(arg[i])) {
            lua_pushboolean(luaState, std::get<bool>(arg[i]));
        } else {
            std::cerr << "Error while pushing lua value '" << i << "': Invalid type" << std::endl;
            return;
        }
        lua_settable(luaState, -3);
    }
};
