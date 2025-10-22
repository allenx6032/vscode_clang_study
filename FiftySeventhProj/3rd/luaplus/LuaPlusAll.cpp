#define LUA_FORCE_USE_LONGJMP
#ifndef LUAPLUS_ALL
#define LUAPLUS_ALL
#endif
#define loslib_c
#include "LuaLink.h"
LUA_EXTERN_C_BEGIN
#include "src/lapi.c.h"
#include "src/lauxlib.c.h"
#include "src/lbaselib.c.h"
#include "src/lcode.c.h"
#include "src/ldblib.c.h"
#include "src/ldebug.c.h"
#include "src/ldo.c.h"
#include "src/ldump.c.h"
#include "src/lfunc.c.h"
#include "src/lgc.c.h"
#include "src/linit.c.h"
#include "src/liolib.c.h"
#include "src/llex.c.h"
#include "src/lmathlib.c.h"
#include "src/lmem.c.h"
#include "src/lobject.c.h"
#include "src/lopcodes.c.h"
#include "src/loslib.c.h"
#include "src/lparser.c.h"
#include "src/lstate.c.h"
#include "src/lstring.c.h"
#include "src/lstrlib.c.h"
#include "src/ltable.c.h"
#include "src/ltablib.c.h"
#include "src/ltm.c.h"
#include "src/lundump.c.h"
#include "src/lvm.c.h"
#include "src/lzio.c.h"
#include "lwstrlib.c.h"
#include "LuaPlusAddons.c.h"
LUA_EXTERN_C_END
#include "LuaPlus.cpp"
#include "LuaPlus_Libs.cpp"
#include "LuaPlusFunctions.cpp"
#include "LuaState.cpp"
#include "LuaStateOutFile.cpp"
#include "LuaState_DumpObject.cpp"
#include "LuaObject.cpp"
#include "LuaTableIterator.cpp"
LUA_EXTERN_C_BEGIN
#include "src/loadlib.c.h"
#if defined(LUA_WIN)
#include "popen.c.h"
#endif // LUA_WIN
LUA_EXTERN_C_END
