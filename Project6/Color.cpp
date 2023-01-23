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
uint32_t Color::colorClassToHex(Color c)
{
	return c.rh * 65536 + c.gs * 256 + c.bv;
}
Color Color::interpolate(Color c1, Color c2, float intensity) {
	return Color(ColorMode::RGB1, c1.rh + intensity * (c2.rh - c1.rh), c1.gs + intensity * (c2.gs - c1.gs), c1.bv + intensity * (c2.bv - c1.bv));
}