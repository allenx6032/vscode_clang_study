#include "LuaConsole.h"

int LuaConsole::Print(lua_State* L)
{
	const char* readString = luaL_checkstring(L, 1);
	CConsole::Print(readString);

	return 0;
}

int LuaConsole::RawLine(lua_State* L)
{
	const char* readString = luaL_checkstring(L, 1);
	printf(readString);

	return 0;
}

int LuaConsole::Clear(lua_State* L)
{
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__)
	system("clear");
#endif
	return 0;
}