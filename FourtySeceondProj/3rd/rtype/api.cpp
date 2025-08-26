//
// Created by Lenny on 30/10/2023.
//

#include "api.hpp"

void initLuaScripts(GameEngine &ge)
{
    ge.luaLoadFile("Common/scripts/enemySimple.lua");
}

float computeEnemySimplePattern(GameEngine &ge, float posX)
{
    float posY = 0;
    ge.luaCallFunction("Common/scripts/enemySimple.lua", "move", 2, posX, posY);
    ge.luaGetReturnValue("Common/scripts/enemySimple.lua", posX, posY);
    return posY;
}
