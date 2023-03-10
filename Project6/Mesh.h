#pragma once
#include "Vector3.h"
#include <vector>
class Mesh
{
public:
	std::vector<Vector3> vertices;
	std::vector<int> triangles;
	static Vector3 calculateCenter(Mesh mesh);
	Mesh(std::vector<Vector3> nvertices, std::vector<int> ntriangles);
	Mesh() = default;
};
