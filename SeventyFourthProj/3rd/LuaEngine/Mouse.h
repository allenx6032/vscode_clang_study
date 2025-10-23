#pragma once
#include "includes.h"

class Mouse
{
public:
	static int SetPosition(lua_State* L);
	static int GetPosition(lua_State* L);
	static int SetState(lua_State* L);
	static int SmoothMove(lua_State* L);
	static int Click(lua_State* L);
};