#pragma once
#include "Matrix.h"
class Vector3
{
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	Vector3(float nx, float ny, float nz);
	Vector3() = default;
	Vector3 operator + (const Vector3 &other) {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
	Vector3 operator - (const Vector3& other) {
		return Vector3(x - other.x, y - other.y, z - other.z);
	}
	Vector3 operator + (const float& other) {
		return Vector3(x + other, y + other, z + other);
	}
	Vector3 operator - (const float& other) {
		return Vector3(x - other, y - other, z - other);
	}
	Vector3 operator * (const float& other) {
		return Vector3(x * other, y * other, z * other);
	}
	Vector3 operator / (const float& other) {
		return Vector3(x / other, y / other, z / other);
	}
	Vector3 operator * (const Vector3& other) {
		return Vector3(x * other.x, y * other.y, z * other.z);
	}
	Vector3 operator / (const Vector3& other) {
		return Vector3(x / other.x, y / other.y, z / other.z);
	}

	operator Matrix() const {
		return Matrix(4, 1, { {x},{y},{z},{1} });
	}
};
