#pragma once
#include "System.h"
#include "AnimatedSprite.h"
#include "Transform.h"
#include "HVMove.h"
#include "Avatar.h"
#include "Video.h"

#include "Timer.h"

class DeltaTimeSystem : public System
{
public:
	void run(World &world) override;

private:
	bool update_animated_sprite(AnimatedSprite *aspr, int delta_time, World &world);
	void update_avatar(Avatar *hvm, int delta_time, World &world);
	void update_timer(int delta_time, World &world);
};
