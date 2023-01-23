#pragma once
#include <string>
enum ColorMode { RGB1, RGB255, HSV };
class Color
{
public:
	float rh;
	float gs;
	float bv;
	ColorMode colorMode;
	Color operator = (const Color& alt) {
		return alt;
	}
	std::stringstream rgbToHex(int r, int g, int b, bool with_head);
	Color(ColorMode colorMode, float nrh, float ngs, float nbv);
	Color() = default;
};

