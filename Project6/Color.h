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
	static uint32_t colorClassToHex(Color c);
	static Color interpolate(Color c1, Color c2, float intensity);
	Color(ColorMode colorMode, float nrh, float ngs, float nbv);
	Color() = default;
};

