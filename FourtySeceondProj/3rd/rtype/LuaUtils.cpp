/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#include "LuaManager.hpp"

void LuaManager::luaLoadFile(const std::string &path)
{
    if (_luaStates[path])
        lua_close(_luaStates[path]);
    _luaStates[path] = luaL_newstate();
    luaL_openlibs(_luaStates[path]);
    // check if path is valid
    if (path.find(".lua") == std::string::npos)
        throw gameEngine::lua::InvalidLuaFile("Invalid file extension");
    // check if file exists
    std::ifstream file(path);
    if (!file || !file.good())
        throw gameEngine::lua::InvalidLuaFile("File does not exist");
    luaL_dofile(_luaStates[path], path.c_str());
};

void LuaManager::luaAddCppFunction(const std::string &fromFile, const std::string &name, lua_CFunction func)
{
    if (_luaStates.find(fromFile) == _luaStates.end())
        throw gameEngine::lua::InvalidLuaFile("File '" + fromFile + "' does not exist");

    // check if function name is valid
    if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos)
        throw gameEngine::lua::InvalidLuaFunction("Invalid function naming for lua");
    lua_register(_luaStates[fromFile], name.c_str(), func);
};

void LuaManager::luaPrintStack(const std::string &fromFile)
{
    if (_luaStates.find(fromFile) == _luaStates.end())
        throw gameEngine::lua::InvalidLuaFile("File '" + fromFile + "' does not exist");

    std::cout << "LUA STACK----------------------------" << std::endl;
    int top = lua_gettop(_luaStates[fromFile]);
    for (int i = 1; i <= top; i++) {
        std::cout << i << "\t" << luaL_typename(_luaStates[fromFile],i) << "\t";
        switch (lua_type(_luaStates[fromFile], i)) {
            case LUA_TNIL:
                std::cout << "nil" << std::endl;
                break;
            case LUA_TBOOLEAN:
                std::cout << "bool: " << (lua_toboolean(_luaStates[fromFile],i) ? "true" : "false") << std::endl;
                break;
            case LUA_TLIGHTUSERDATA:
                std::cout << "lightuserdata" << std::endl;
                break;
            case LUA_TNUMBER:
                std::cout << "number: " << lua_tonumber(_luaStates[fromFile],i) << std::endl;
                break;
            case LUA_TSTRING:
                std::cout << "string: " << lua_tostring(_luaStates[fromFile],i) << std::endl;
                break;
            case LUA_TTABLE:
                std::cout << "table" << std::endl;
                break;
            case LUA_TFUNCTION:
                std::cout << "function" << std::endl;
                break;
            case LUA_TUSERDATA:
                std::cout << "userdata" << std::endl;
                break;
            default:
                std::cout << lua_typename(_luaStates[fromFile], lua_type(_luaStates[fromFile], i)) << std::endl;
                break;
        }
    }
    std::cout << "END OF LUA STACK---------------------" << std::endl;
};