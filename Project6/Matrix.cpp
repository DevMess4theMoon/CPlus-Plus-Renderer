#include "Matrix.h"

Matrix::Matrix(int nsx, int nsy, double default_value) : sx(nsx), sy(nsy)
{
	m = std::vector<std::vector<double>>(nsx, std::vector<double>(sy, default_value));
}

Matrix::Matrix(int nsx, int nsy, std::vector<std::vector<double>> default_value) : sx(nsx), sy(nsy), m(default_value) {}

