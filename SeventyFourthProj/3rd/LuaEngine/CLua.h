#pragma once

#include "includes.h"

class CLua
{
public:
	static void DoString(char* code);
	static void DoFile(char* path);
};