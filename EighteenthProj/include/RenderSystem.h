#pragma once
#include "System.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Transform.h"
#include "HVTile.h"
#include "HVMove.h"
#include "Avatar.h"
#include "Video.h"
#include "Npc.h"
#include "FootHold.h"
#include "Line.h"

class RenderSystem : public System
{
public:
	void run(World &world) override;

private:
	void render_sprite(Transform *tr, Sprite *spr, World &world);
	void render_animated_sprite(Transform *tr, AnimatedSprite *aspr, World &world);
	void render_hvtile_sprite(Transform *tr, HVTile *hvt, World &world);
	void render_avatar_sprite(Transform *tr, Avatar *ava, World &world);
	void render_video(Transform *tr,Video *vid, World &world);
	void render_fh(FootHold *fh,World &world);
};
