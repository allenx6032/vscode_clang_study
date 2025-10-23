#include "Engine.h"

wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

int Engine::Wait(lua_State* L)
{
	int time = luaL_checkinteger(L, 1);
	Sleep(time);
	return 0;
}

int Engine::ShowMessageBox(lua_State* L)
{
	const char* title = luaL_checkstring(L, 1);
	const char* info = luaL_checkstring(L, 2);
	int type = luaL_checkinteger(L, 3);

	int result = MessageBox(0, convertCharArrayToLPCWSTR(info), convertCharArrayToLPCWSTR(title), type);

	lua_pushinteger(L, result);

	return result;
}