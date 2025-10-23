#include "CLua.h"

static const luaL_Reg consoleLib[] = {
	{"print",				LuaConsole::Print},									// console.print(string: text)
	{"rawline",				LuaConsole::RawLine},								// console.rawline(string: text)
	{"clear",				LuaConsole::Clear},									// console.clear()
	{NULL, NULL}
};

static const luaL_Reg mouseLib[] = {
	{"setPosition",			Mouse::SetPosition},								// mouse.setPosition(int: x, int: y)
	{"getPosition",			Mouse::GetPosition},								// mouse.getPosition()
	{"smoothMove",			Mouse::SmoothMove},									// mouse.smoothMove(int: x, int: y, int: time, int: interpolations)
	{"setState",			Mouse::SetState},									// mouse.setState(int: button, bool: state)
	{"click",				Mouse::Click},										// mouse.click(int: x, int: y, int: button, int:time)
	{NULL, NULL}
};

static const luaL_Reg keyboardLib[] = {
	{"getKeyState",			Keyboard::GeyKeyState},								// keyboard.getKeyState(int: key)
	{"getAsyncKeyState",	Keyboard::GeyAsyncKeyState},						// keyboard.getAsyncKeyState(int: key)
	{"setKeyState",			Keyboard::SetKeyState},								// keyboard.setKeyState(int: key, bool: state)
	{"execute",				Keyboard::Execute},									// keyboard.execute(string: text)
	{NULL, NULL}
};

static const luaL_Reg drawingLib[] = {
	{"getDimensions",		Screen::GetDimensions},								// screen.getDimensions()
	{"getPixelColor",		Screen::GetPixelColor},								// screen.getPixelColor(int: x, int: y)
	{"findPixelByColor",	Screen::FindPixelByColor},							// screen.findPixelByColor(int: x, int: y, int: w, int: h, int: r, int: g, int: b, int: variation)
	{NULL, NULL}
};

static const luaL_Reg engineLib[] = {
	{"wait",				Engine::Wait},										// engine.wait(int: time)
	{"messageBox",			Engine::ShowMessageBox},							// engine.messageBox(string: title, string: info, int: type)
	{NULL, NULL}
};

class LuaScript
{
	lua_State* L = NULL;

public:
	LuaScript()
	{
		L = luaL_newstate();
		luaL_openlibs(L);

		lua_newtable(L);
		luaL_setfuncs(L, consoleLib, 0);
		lua_setglobal(L, "console");

		lua_newtable(L);
		luaL_setfuncs(L, mouseLib, 0);
		lua_setglobal(L, "mouse");

		lua_newtable(L);
		luaL_setfuncs(L, keyboardLib, 0);
		lua_setglobal(L, "keyboard");

		lua_newtable(L);
		luaL_setfuncs(L, drawingLib, 0);
		lua_setglobal(L, "screen");

		lua_newtable(L);
		luaL_setfuncs(L, engineLib, 0);
		lua_setglobal(L, "engine");


		KeyCodes::Define(L);
	}

	void doString(const char* code)
	{
		if (luaL_dostring(L, code) != LUA_OK)
		{
			printf("Error: %s\n", lua_tostring(L, -1));
		}
	}

	void doFile(const char* file)
	{
		if (luaL_dofile(L, file) != LUA_OK)
		{
			printf("Error: %s\n", lua_tostring(L, -1));
		}
	}

	void closeState()
	{
		lua_close(L);
	}
};

void CLua::DoString(char* code)
{
	LuaScript state;
	state.doString(code);
	state.closeState();
}

void CLua::DoFile(char* path)
{
	LuaScript state;
	state.doFile(path);
	state.closeState();
}