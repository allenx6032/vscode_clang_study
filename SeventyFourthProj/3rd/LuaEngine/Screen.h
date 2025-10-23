#pragma once
#include "includes.h"

class Screen
{
public:
	static int GetDimensions(lua_State* L);
	static int GetPixelColor(lua_State* L);
	static int FindPixelByColor(lua_State* L);
};