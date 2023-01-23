#include "Color.h"
#include <cmath>
#include <sstream>
Color::Color(ColorMode ncolorMode, float nrh, float ngs, float nbv) {
	colorMode = ncolorMode;
	rh = nrh;
	gs = ngs;
	bv = nbv;
}
std::string Color::rgbToHex(int r, int g, int b, bool with_head)
{
    std::stringstream ss;
    if (with_head)
        ss << "0x";
    ss << std::hex << (r << 16 | g << 8 | b);
    return ss.str();
}
