#include "Keyboard.h"

int Keyboard::GeyKeyState(lua_State* L)
{
	int key = luaL_checkinteger(L, 1);
	lua_pushboolean(L, (GetKeyState(key) & 0x8000));

	return 1;
}

int Keyboard::GeyAsyncKeyState(lua_State* L)
{
	int key = luaL_checkinteger(L, 1);
	lua_pushboolean(L, (GetAsyncKeyState(key) & 0x01));

	return 1;
}

void SendKey(int key, bool state)
{
	INPUT input;
	WORD vkey = (WORD)key;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	input.ki.dwFlags = (state ? 0 : KEYEVENTF_KEYUP);
	SendInput(1, &input, sizeof(INPUT));
}

int Keyboard::SetKeyState(lua_State* L)
{
	int key = luaL_checkinteger(L, 1);
	bool state = lua_toboolean(L, 2);

	SendKey(key, state);

	return 0;
}

int Keyboard::Execute(lua_State* L)
{
	const char* text = luaL_checkstring(L, 1);

	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	HKL kbl = GetKeyboardLayout(0);

	for (char& c : (string)text)
	{
		ip.ki.wVk = VkKeyScanExA(c, kbl);
		ip.ki.dwFlags = 0;
		SendInput(1, &ip, sizeof(ip));
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(ip));
	}

	return 0;
}