#include "RoomManager.h"

#include <limits>

#include "LuaWrapper/LuaWrapper.h"

int test(int x, int y)
{
	std::cout << "TEST" << std::endl;
	return x;
}

int main(void)
{
	RoomManager rm;

	rm.Init();

	std::cout << "Press Enter key to quit...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}