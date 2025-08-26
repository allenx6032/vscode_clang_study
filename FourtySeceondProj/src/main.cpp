#include "gameServer.hpp"

#define TCP_PORT 6000

int main(int ac, char **av)
{
    std::string buffer;
    if (ac < 2)
        buffer = "127.0.0.1";
    else
        buffer = av[1];

    GameServer server(TCP_PORT, buffer);
    server.run();
    return 0;
}
