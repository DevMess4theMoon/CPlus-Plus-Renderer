#pragma once
#include <vector>
#include <iostream>
class Matrix
{
public:
	std::vector<std::vector<double>> m;
	Matrix(int nsx, int nsy, double default_value);
	Matrix(int nsx, int nsy, std::vector<std::vector<double>> default_value);
	Matrix() = default;
	int sx;
	int sy;
	static Matrix im(int s) {
		Matrix temp(s, s, 0);
		for (int x = 0; x < s; x++) {
			temp.m[x][x] = 1;
		}
		return temp;
	}
	Matrix operator + (const Matrix& other) {
		if (other.sx != sx || other.sy != sy) {
			return Matrix(sx, sy, 0);
		}
		else {
			std::vector<std::vector<double>> temp = m;
			for (int r = 0; r < sx; r++) {
				for (int v = 0; v < sy; v++) {
					temp[r][v] = m[r][v] + other.m[r][v];
				}
			}
			return Matrix(sx, sy, temp);
		}
	}
	Matrix operator - (const Matrix& other) {
		if (other.sx != sx || other.sy != sy) {
			return Matrix(sx, sy, 0);
		}
		else {
			std::vector<std::vector<double>> temp = m;
			for (int r = 0; r < sx; r++) {
				for (int v = 0; v < sy; v++) {
					temp[r][v] = m[r][v] - other.m[r][v];
				}
			}
			return Matrix(sx, sy, temp);
		}
	}
	Matrix operator * (const Matrix& other) {
		if (sy != other.sx) {
			return Matrix(sx, sy, 0);
		}

		std::vector<std::vector<double>> result(sx, std::vector<double>(other.sy, 0));
		for (int x = 0; x < sx; x++) {
			for (int y = 0; y < other.sy; y++) {
				for (int r = 0; r < sy; r++) {

					result[x][y] += m[x][r] * other.m[r][y];		

				}
			}
		}
		return Matrix(sx, other.sy, result);
	}
};