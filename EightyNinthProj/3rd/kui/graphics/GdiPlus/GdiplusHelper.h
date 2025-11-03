#pragma once

#include <windows.h>
#include <Gdiplus.h>
#include "kui/UIDefine.h"
#include "kui/Color.h"
#include "kui/KFont.h"
#include "kui/KPoint.h"
#include "kui/Brush.h"

namespace GdiplusHelper
{
	Gdiplus::Color colorToGdiplusColor(Color color);
	Gdiplus::Font* fontToGdiplusFont(const KFont& font);
	Gdiplus::PointF pointToGdiplusPointF(const KPoint& point);
	Gdiplus::Brush* brushToGdiplusBrush(KBrush* brush);
	Gdiplus::CombineMode opModeToGdiplusCombineMode(ak::opMode mode);
}