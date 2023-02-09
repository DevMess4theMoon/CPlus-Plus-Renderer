#pragma once
#include "Matrix.h"
class Rotation
{
public:
	static Matrix rotZ(float amount, bool twod) {
		Matrix temp;
		if (twod) {
			temp = Matrix(2, 2, { {(float)cos(amount),(float)-sin(amount)},{(float)sin(amount),(float)cos(amount)} });
		}
		else {
			temp = Matrix(3, 3, {
			{(float)cos(amount),(float)-sin(amount), 0 },
			{(float)sin(amount),(float)cos(amount), 0 },
			{ 0,0,1 }
			});
		}
	}
	static Matrix rotY(float amount) {
		Matrix temp;
		temp = Matrix(3, 3, {
			{(float)cos(amount), 0, (float)sin(amount)},
			{0,1,0},
			{(float)-sin(amount), 0, (float)cos(amount)}
			});
		return temp;
	}
	static Matrix rotX(float amount) {
		Matrix temp;
		temp = Matrix(3, 3, {
			{ 1,0,0 },
			{0, (float)cos(amount),(float)-sin(amount)},
			{0, (float)sin(amount),(float)cos(amount),}
			});
		return temp;
	}
};

