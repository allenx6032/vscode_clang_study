#ifndef LUA_RAYLIB_H
#define LUA_RAYLIB_H

#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
#include <string.h>
#include <stdlib.h>
#include <raylib/raylib.h>

void push_color(lua_State *L, Color color);
void register_raylib_colors(lua_State *L);

#endif