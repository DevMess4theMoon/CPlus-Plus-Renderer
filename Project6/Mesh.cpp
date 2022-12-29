#include "Mesh.h"
#include <iostream>
#include <vector>
Mesh::Mesh(std::list<Vector3> nvertices, std::list<int> ntriangles) {
	if (sizeof(nvertices) >= 3) {
		vertices = nvertices;
	}
	if (sizeof(ntriangles) % 3 == 0) {
		triangles = ntriangles;
	}
}