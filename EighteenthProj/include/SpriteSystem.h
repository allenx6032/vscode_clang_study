#pragma once
#include "System.h"
#include "DistanceSprite.h"
#include "Transform.h"

class SpriteSystem : public System
{
public:
	void run(World &world) override;

private:
	void update_dis(DistanceSprite *dis, World &world);
};
