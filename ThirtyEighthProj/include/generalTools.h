#ifndef GENERALTOOLS_H
#define GENERALTOOLS_H
#include "Board.h"
#include "Tileset.h"
#include "Board.h"

Tileset edgeTiles(Board* toTest, bool goingRight);
int getRandomNumber(int low, int high);
Tile* getRandomTile(Tileset* myTileset);

#endif