#include "Matrix.h"

Matrix::Matrix(int nsx, int nsy, float default_value) {
	sx = nsx;
	sy = nsy;
	for (int y = 0; y < nsy; y++) {
		std::vector<float> temp = {};
		for (int x = 0; x < nsy; x++)
		{
			temp.push_back(default_value);
		}
		m.push_back(temp);
	}
}

Matrix::Matrix(int nsx, int nsy, std::vector<std::vector<float>> default_value) {
	sx = nsx;
	sy = nsy;
	m = default_value;
}

