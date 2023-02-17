#pragma once
#include "Matrix.h"
#include "Mesh.h"
#include "Vector3.h"
#include <vector>
class Rotation
{
public:
	static Matrix rotX(double amount);
	static Matrix rotY(double amount);
	static Matrix rotZ(double amount);
	static Mesh rotMesh(Mesh mesh, Vector3 rotation , Vector3 center);
};

