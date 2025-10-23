#pragma once
#include "includes.h"

class Engine
{
public:
	static int Wait(lua_State* L);
	static int ShowMessageBox(lua_State* L);
};