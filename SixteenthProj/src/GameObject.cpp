#include <sdl/SDL.h>
#include <sdl/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <tinyxml2.h>
#include <box2d/Box2D.h>
#include "GameDebug.hpp"
#include "Global.h"

// #pragma comment(lib, "tinyxml2.lib")

using namespace std;

#include "SpawnManager.hpp"
#include "Input.hpp"
#include "MessageDispatch.hpp"
#include "Box.hpp"
#include "GameUtils.hpp"
#include "RelativeSpace.hpp"
#include "AnimatedSprite.hpp"
#include "ItemDrop.hpp"
#include "Game.hpp"
#include "GameObject.h"

GAMEObject::GAMEObject()
{

}

GAMEObject::~GAMEObject()
{

}


