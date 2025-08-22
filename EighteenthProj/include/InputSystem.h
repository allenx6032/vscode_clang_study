#pragma once
#include "System.h"
#include "Transform.h"
#include "Physic/Normal.h"
#include "Player.h"
#include "RandomInput.h"

class InputSystem : public System
{
public:
	void run(World &world) override;

private:
	void update_player(Player *nor, World &world);
	void update_random_input(RandomInput *ran, World &world);
};
