#include "CConsole.h"

bool CConsole::Print(const char* text)
{
    time_t currentTime;
    struct tm* localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);

	printf("[CConsole] [%02d:%02d:%02d] %s\n", localTime->tm_hour, localTime->tm_min, localTime->tm_sec, text);
	return true;
}