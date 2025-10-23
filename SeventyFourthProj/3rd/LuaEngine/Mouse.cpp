#include "Mouse.h"

int Mouse::SetPosition(lua_State* L)
{
	int x = luaL_checkinteger(L, 1);
	int y = luaL_checkinteger(L, 2);
	SetCursorPos(x, y);

	return 0;
}
int Mouse::GetPosition(lua_State* L)
{
	POINT p;
	GetCursorPos(&p);

	lua_pushinteger(L, p.x);
	lua_pushinteger(L, p.y);

	return 2;
}


int Mouse::SetState(lua_State* L)
{
	int button = luaL_checkinteger(L, 1);
	bool state = lua_toboolean(L, 2);

	if (button == 1) {
		if ((!state && ((GetKeyState(VK_LBUTTON) & 0x8000) != 0)) || (state && ((GetKeyState(VK_LBUTTON) & 0x8000) == 0)))
		{
			mouse_event(state ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}
	else if (button == 2)
	{
		if ((!state && ((GetKeyState(VK_RBUTTON) & 0x8000) != 0)) || (state && ((GetKeyState(VK_RBUTTON) & 0x8000) == 0)))
		{
			mouse_event(state ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		}
	}

	return 0;
}

int Mouse::Click(lua_State* L)
{
	int x = luaL_checkinteger(L, 1);
	int y = luaL_checkinteger(L, 2);
	int button = luaL_checkinteger(L, 3);
	int time = luaL_checkinteger(L, 4);

	SetCursorPos(x, y);

	mouse_event((button == 1 ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN), 0, 0, 0, 0);
	Sleep(time);
	mouse_event((button == 1 ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP), 0, 0, 0, 0);

	return 0;
}

int Mouse::SmoothMove(lua_State* L)
{
	POINT p;
	GetCursorPos(&p);

	int x = luaL_checkinteger(L, 1);
	int y = luaL_checkinteger(L, 2);
	int time = luaL_checkinteger(L, 3);

	float start = (float)clock();
	float end = (float)start + (float)time;

	printf("%f, %f", start, end);

	while ((float)clock() < end)
	{
		float prg = ((float)clock() - start) / (float)time;
		SetCursorPos(p.x + (x - p.x) * prg, p.y + (y - p.y) * prg);
	}
	
	return 0;
}