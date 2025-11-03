// #include "Stdafx.h"
#include "GdiplusAnimatorView.h"
#include "kui/Image.h"
#include "demo.h"
#include "kui/KPoint.h"

const int IMAGE_WIDTH = 128;

GdiplusAnimatorView::GdiplusAnimatorView()
{
	init();
}

GdiplusAnimatorView::~GdiplusAnimatorView()
{

}

// Image* GdiplusAnimatorView::createImage()
// {
// 	return Image::createImage(ak::GdiPlusGraphics);
// }