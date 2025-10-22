#ifndef LUNAVG_INTERNAL_H
#define LUNAVG_INTERNAL_H

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LUA_COMPAT_APIINTCASTS
#define NANOVG_GL2_IMPLEMENTATION

#include <GLew/glew.h>

#include <lua/lua.h>

#include "lua/lualib.h"
#include "lua/lauxlib.h"
#include "luaautoc/lautoc.h"

#include "nanovg/nanovg.h"
#include "nanovg/nanosvg.h"
#include "nanovg/nanovg_gl.h"

#include "lunavg.h"

int luaopen_lunavg(lua_State *L);

#endif
