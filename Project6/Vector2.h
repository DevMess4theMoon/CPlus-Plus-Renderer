#pragma once
#include "Matrix.h"
class Vector2
{
public:
	float x = 0.0f;
	float y = 0.0f;
	Vector2(float nx, float ny);
	Vector2() = default;
	Vector2 operator + (const Vector2 &other) {
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 operator - (const Vector2& other) {
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 operator + (const float& other) {
		return Vector2(x + other, y + other);
	}
	Vector2 operator - (const float& other) {
		return Vector2(x - other, y - other);
	}
	Vector2 operator * (const float& other) {
		return Vector2(x * other, y * other);
	}
	Vector2 operator / (const float& other) {
		return Vector2(x / other, y / other);
	}
	Vector2 operator * (const Vector2& other) {
		return Vector2(x * other.x, y * other.y);
	}
	Vector2 operator / (const Vector2& other) {
		return Vector2(x / other.x, y / other.y);
	}
	Vector2 operator += (const Vector2& other) {
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 operator -= (const Vector2& other) {
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 operator += (const float& other) {
		return Vector2(x + other, y + other);
	}
	Vector2 operator -= (const float& other) {
		return Vector2(x - other, y - other);
	}
	Vector2 operator *= (const float& other) {
		return Vector2(x * other, y * other);
	}
	Vector2 operator /= (const float& other) {
		return Vector2(x / other, y / other);
	}
	Vector2 operator *= (const Vector2& other) {
		return Vector2(x * other.x, y * other.y);
	}
	Vector2 operator /= (const Vector2& other) {
		return Vector2(x / other.x, y / other.y);
	}
	operator Matrix() const {
		return Matrix(1, 2, { {x},{y} });
	}
};

