#include "includes.h"

using namespace std;

std::string GetCurrentDirectory()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");

    return std::string(buffer).substr(0, pos);
}

void StartNewCommand()
{
    string command;

    getline(std::cin, command);

    if (command.rfind("run ", 0) == 0)
    {
        string code = command.substr(4);

        char* charCode = new char[code.length() + 1];
        strcpy(charCode, code.c_str());

        CLua::DoString(charCode);
    }
    else if (command.rfind("runfile ", 0) == 0)
    {
        string path = command.substr(8);

        if (path.rfind("\\") == -1) {
            path = GetCurrentDirectory() + "\\" + path;
        }

        char* charPath = new char[path.length() + 1];
        strcpy(charPath, path.c_str());

        CLua::DoFile(charPath);
    }
    else
    {
        char* code = new char[command.length() + 1];
        strcpy(code, command.c_str());

        CLua::DoString(code);
    }

    StartNewCommand();
}

int main(int argc, char** argv)
{
    SetConsoleOutputCP(65001);

    if (!argv[1])
    {
        StartNewCommand();
    }
    else
    {
        CLua::DoFile(argv[1]);
        printf("\nPress CTRL + C to terminate program.\n");
        while (true) {}
    }
}