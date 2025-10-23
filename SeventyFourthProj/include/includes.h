#pragma once

#pragma warning(disable:4244)
#pragma warning(disable:4305)
#pragma warning(disable:4309)
#pragma warning(disable:4005)
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

#include <memory>
#include <iostream>
#include "Windows.h"
#include "time.h"
#include <format>
#include <cstdarg>
#include <string>

// Lua
extern "C" {
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

#include "LuaEngine/Mouse.h"
#include "LuaEngine/Keyboard.h"
#include "LuaEngine/LuaConsole.h"
#include "LuaEngine/KeyCodes.h"
#include "LuaEngine/Screen.h"
#include "LuaEngine/Engine.h"

#include "LuaEngine/CConsole.h"
#include "LuaEngine/CLua.h"