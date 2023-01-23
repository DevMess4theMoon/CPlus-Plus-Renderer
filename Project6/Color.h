#pragma once
#include <string>
#include <cstdint>
#include <fcntl.h>
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
	static uint32_t rgbToHex(int r, int g, int b);
	Color(ColorMode colorMode, float nrh, float ngs, float nbv);
	Color() = default;
};

