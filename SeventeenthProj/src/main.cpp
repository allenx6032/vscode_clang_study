#pragma once
#include "Menu.h"

int main() try
{
    auto m = Menu();
    m.run();
}
catch (std::exception& ex)
{
	std::cerr << "Exception: " << ex.what() << '\n';
	return EXIT_FAILURE;
}
catch (...)
{
	std::cerr << "Unknown exception\n";
	return EXIT_FAILURE;
} 