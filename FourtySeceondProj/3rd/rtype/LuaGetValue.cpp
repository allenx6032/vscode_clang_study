/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#include "LuaManager.hpp"

void LuaManager::luaGetValueFromStack(lua_State *luaState, std::string &returnValue, size_t nbArgs)
{
    returnValue = luaL_checkstring(luaState, -nbArgs);
    lua_remove(luaState, -nbArgs);
};

void LuaManager::luaGetValueFromStack(lua_State *luaState, int &returnValue, size_t nbArgs)
{
    returnValue = luaL_checkinteger(luaState, -nbArgs);
    lua_remove(luaState, -nbArgs);
};

void LuaManager::luaGetValueFromStack(lua_State *luaState, float &returnValue, size_t nbArgs)
{
    returnValue = luaL_checknumber(luaState, -nbArgs);
    lua_remove(luaState, -nbArgs);
};

void LuaManager::luaGetValueFromStack(lua_State *luaState, double &returnValue, size_t nbArgs)
{
    returnValue = luaL_checknumber(luaState, -nbArgs);
    lua_remove(luaState, -nbArgs);
};

void LuaManager::luaGetValueFromStack(lua_State *luaState, bool &returnValue, size_t nbArgs)
{
    returnValue = luaL_checkinteger(luaState, -nbArgs);
    lua_remove(luaState, -nbArgs);
};

void LuaManager::luaGetValueFromStack(lua_State *luaState, LUA_TABLE_MAP_TYPE &returnValue, size_t nbArgs)
{
    if (lua_isnil(luaState, -nbArgs))
        return;
    if (!lua_istable(luaState, -nbArgs))
        return;
    lua_pushnil(luaState);
    while (lua_next(luaState, -nbArgs-1) != 0) {
        if (lua_isstring(luaState, -1)) {
            returnValue[lua_tostring(luaState, -2)] = std::string(lua_tostring(luaState, -1));
        } else if (lua_isinteger(luaState, -1)) {
            returnValue[lua_tostring(luaState, -2)] = (int)lua_tointeger(luaState, -1);
        } else if (lua_isnumber(luaState, -1)) {
            returnValue[lua_tostring(luaState, -2)] = lua_tonumber(luaState, -1);
        } else if (lua_isboolean(luaState, -1)) {
            returnValue[lua_tostring(luaState, -2)] = lua_toboolean(luaState, -1);
        } else {
            std::cerr << "Error while getting lua value '" << lua_tostring(luaState, -2) << "': Invalid type" << std::endl;
            return;
        }
        lua_pop(luaState, 1);
    }
    lua_remove(luaState, -nbArgs);
};

void LuaManager::luaGetValueFromStack(lua_State *luaState, LUA_TABLE_VECTOR_TYPE &returnValue, size_t nbArgs)
{
    if (lua_isnil(luaState, -nbArgs))
        return;
    if (!lua_istable(luaState, -nbArgs))
        return;
    lua_pushnil(luaState);
    while (lua_next(luaState, -nbArgs-1) != 0) {
        if (lua_isstring(luaState, -1)) {
            returnValue.push_back(std::string(lua_tostring(luaState, -1)));
        } else if (lua_isinteger(luaState, -1)) {
            returnValue.push_back((int)lua_tointeger(luaState, -1));
        } else if (lua_isnumber(luaState, -1)) {
            returnValue.push_back(lua_tonumber(luaState, -1));
        } else if (lua_isboolean(luaState, -1)) {
            returnValue.push_back(lua_toboolean(luaState, -1));
        } else {
            std::cerr << "Error while getting lua value '" << lua_tostring(luaState, -2) << "': Invalid type" << std::endl;
            return;
        }
        lua_pop(luaState, 1);
    }
    lua_remove(luaState, -nbArgs);
};
