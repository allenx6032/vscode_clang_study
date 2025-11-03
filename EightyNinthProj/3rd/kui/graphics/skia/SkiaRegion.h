#pragma once

#include "kui/KRegion.h"

class SkRegion;

class SkiaRegion : public KRegion
{
public:
	SkiaRegion();
	virtual ~SkiaRegion();

	SkRegion* getRegion();

private:
	SkRegion* _region;
};