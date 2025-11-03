#include "UIDefine.h"
#include "SolidBrush.h"

SolidBrush::SolidBrush(const Color& color)
	: _color(color)
{

}

SolidBrush::~SolidBrush()
{

}

ak::BrushType SolidBrush::getBrushType()
{
	return ak::BrushType::SolidBrush;
}

Color SolidBrush::getColor() const
{
	return _color;
}

void SolidBrush::setColor(const Color& color)
{
	_color = color;
}