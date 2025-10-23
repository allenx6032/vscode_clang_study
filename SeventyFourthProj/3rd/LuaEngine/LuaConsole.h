#pragma once
#include "includes.h"

class LuaConsole
{
public:
	static int Print(lua_State* L);
	static int RawLine(lua_State* L);
	static int Clear(lua_State* L);
};