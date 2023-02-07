#pragma once
#include <vector>
class Matrix
{
public:
	std::vector<std::vector<float>> m;
	Matrix(int nsx, int nsy, float default_value);
	Matrix(int nsx, int nsy, std::vector<std::vector<float>> default_value);
	Matrix() = default;
	float sx;
	float sy;
	Matrix operator + (const Matrix& other) {
		if (other.sx != sx || other.sy != sy) {
			return Matrix(sx, sy, 0);
		}
		else {
			std::vector<std::vector<float>> temp = m;
			for (int r = 0; r < sx; r++) {
				for (int v = 0; v < sy; v++) {
					temp[r][v] = m[r][v] + other.m[r][v];
				}
			}
			return Matrix(sx, sy, temp);
		}
	}
};