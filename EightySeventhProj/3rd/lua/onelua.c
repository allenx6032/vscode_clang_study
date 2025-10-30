/*
** Lua core, libraries, and interpreter in a single file.
** Compiling just this file generates a complete Lua stand-alone
** program:
**
** $ gcc -O2 -std=c99 -o lua onelua.c -lm
**
** or
**
** $ gcc -O2 -std=c89 -DLUA_USE_C89 -o lua onelua.c -lm
**
*/
#define MAKE_LIB

/* default is to build the full interpreter */
#ifndef MAKE_LIB
#ifndef MAKE_LUAC
#ifndef MAKE_LUA
#define MAKE_LUA
#endif
#endif
#endif


/*
** Choose suitable platform-specific features. Default is no
** platform-specific features. Some of these options may need extra
** libraries such as -ldl -lreadline -lncurses
*/
#if 0
#define LUA_USE_LINUX
#define LUA_USE_MACOSX
#define LUA_USE_POSIX
#define LUA_ANSI
#endif


/* no need to change anything below this line ----------------------------- */

#include "lprefix.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* setup for luaconf.h */
#define LUA_CORE
#define LUA_LIB
#define ltable_c
#define lvm_c
#include "luaconf.h"

/* do not export internal symbols */
#undef LUAI_FUNC
#undef LUAI_DDEC
#undef LUAI_DDEF
#define LUAI_FUNC	static
#define LUAI_DDEC(def)	/* empty */
#define LUAI_DDEF	static

/* core -- used by all */
#include "lzio.c.h"
#include "lctype.c.h"
#include "lopcodes.c.h"
#include "lmem.c.h"
#include "lundump.c.h"
#include "ldump.c.h"
#include "lstate.c.h"
#include "lgc.c.h"
#include "llex.c.h"
#include "lcode.c.h"
#include "lparser.c.h"
#include "ldebug.c.h"
#include "lfunc.c.h"
#include "lobject.c.h"
#include "ltm.c.h"
#include "lstring.c.h"
#include "ltable.c.h"
#include "ldo.c.h"
#include "lvm.c.h"
#include "lapi.c.h"

/* auxiliary library -- used by all */
#include "lauxlib.c.h"

/* standard library  -- not used by luac */
#ifndef MAKE_LUAC
#include "lbaselib.c.h"
#include "lcorolib.c.h"
#include "ldblib.c.h"
#include "liolib.c.h"
#include "lmathlib.c.h"
#include "loadlib.c.h"
#include "loslib.c.h"
#include "lstrlib.c.h"
#include "ltablib.c.h"
#include "lutf8lib.c.h"
#include "linit.c.h"
#endif

/* lua */
#ifdef MAKE_LUA
#include "lua.c.h"
#endif

/* luac */
#ifdef MAKE_LUAC
#include "luac.c.h"
#endif
