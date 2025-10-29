#include <iostream>
#include <Windows.h>
#include <thread>
#include "engine/lua/Clua.h"
#include "engine/utils/KeyState.h"
#include "engine/utils/console/console.h"
#include "engine/config/config.h"
#include "engine/gui/gui.h"

void init() {
	if (!g_console.allocate("Debug"))
		std::abort();

	g_console.log("INIT");

	// redirect warnings to a window similar to errors.
	// _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);

	lua::init_state();

	g_config.init();
	g_config.Default();

	if (!g_gui.init())
	{
		g_console.log("Error_Gui_Init");
		std::abort();
	}

	lua::init_command();
}
void load() {
	for (auto hk : lua::hooks->getHooks("on_load"))
	{
		try
		{
			auto result = hk.func();
			if (!result.valid()) {
				sol::error err = result;
				g_console.log(err.what());
			}
		}
		catch (const std::exception&)
		{

		}
	}
}
void wait() {
	g_console.log("WAIT");
	lua::init_console();
}
void unload() {
	for (auto hk : lua::hooks->getHooks("on_unload"))
	{
		try
		{
			auto result = hk.func();
			if (!result.valid()) {
				sol::error err = result;
				g_console.log(err.what());
			}
		}
		catch (const std::exception&)
		{

		}
	}
	g_console.log("UNLOAD");
	g_console.detach();
}

int main()
{
	try
	{
		//INIT
		init();

		//LOAD
		load();

		//WAIT
		wait();

		//UNLOAD
		unload();
	}
	catch (const std::exception&)
	{
		g_console.log("ERROR");
		g_console.detach();
	}
    return TRUE;
}
