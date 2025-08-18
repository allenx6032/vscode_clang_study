#pragma once

#define STRING_LEN 1024

#define VERSION_MAJOR 0
#define VERSION_MINOR 9
#define VERSION_PATCH 0
#define VERSION_DEV 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "glad.h"
#include "stb_rect_pack.h"

#define PLATFORM_DESKTOP

#ifdef PLATFORM_DESKTOP
	#include "glfw/glfw3.h"
	#include "glfw/glfw3native.h"
#elif PLATFORM_DESKTOP_SDL2
	#include <SDL2/SDL.h>
#elif PLATFORM_DESKTOP_SDL3
	#include <SDL3/SDL.h>
#endif

#ifdef SHARED
	#include <raylib/raylib.h>
	#include <raylib/rlgl.h>
	#include <raylib/raymath.h>
	#include <raygui.h>
	#include <rlights.h>
	#include <raylib/rcamera.h>
#else
	#include "raylib/raylib.h"
	#include "raylib/rlgl.h"
	#include "raylib/raymath.h"
	#include "raygui.h"
	#include "rlights.h"
	#include "raylib/rcamera.h"
#endif

#ifdef LUAJIT
	#ifdef SHARED
		#include <lua/lua.h>
		#include <lua/luajit.h>
		#include <lua/lualib.h>
		#include <lua/lauxlib.h>
	#else
		#include "luajit/lua.h"
		#include "luajit/luajit.h"
		#include "luajit/lualib.h"
		#include "luajit/lauxlib.h"
	#endif
#else
	#ifdef SHARED
		#include <lua/lua.h>
		#include <lua/lualib.h>
		#include <lua/lauxlib.h>
	#else
		#include "lua/lua.h"
		#include "lua/lualib.h"
		#include "lua/lauxlib.h"
	#endif
#endif
