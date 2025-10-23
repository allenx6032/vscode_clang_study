#pragma once
#include "includes.h"

class Keyboard
{
public:
	static int GeyKeyState(lua_State* L);
	static int GeyAsyncKeyState(lua_State* L);
	static int SetKeyState(lua_State* L);
	static int Execute(lua_State* L);
};