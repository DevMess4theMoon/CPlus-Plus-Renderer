#pragma once
#include "Vector3.h"
#include <list>
class Mesh
{
public:
	std::list<Vector3> vertices;
	std::list<int> triangles;
	Mesh(std::list<Vector3> nvertices, std::list<int> ntriangles);
	Mesh() = default;
};
