#pragma once

#include <string>

struct Data
{
	int level = 1;					// player level
	int EXP = 0;					// current experience points
	int MaxEXP = 15;				// amount needed to level up
	int mesos = 0;					// game currency
	int HP = 50;					// health points
	int MaxHP = 50;					// maxiumum health points
	int MP = 50;					// mana points
	int MaxMP = 50;		   		    // maximum mana points
	int damage = 3;					// amount of damage dealt
	float Speed = 140.f;		    // movement speed
	bool wasHit = false;			// for hit detection
	bool dead = false;				// is object dead?
	bool respawn = false;			// should object respawn?
	std::string job = "Beginner";	// current job
	std::string name;

	// monster rewards
	int expReward;
	int mesosReward;
};