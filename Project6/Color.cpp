#include "Color.h"
#include <string>
#include <cmath>
#include <sstream>
#include "MainWindow.h"
Color::Color(ColorMode ncolorMode, float nrh, float ngs, float nbv) {
	colorMode = ncolorMode;
	rh = nrh;
	gs = ngs;
	bv = nbv;
}
uint32_t Color::rgbToHex(int r, int g, int b)
{
	return r * 65536 + g * 256 + b;
}