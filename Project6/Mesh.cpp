#include "Mesh.h"
Mesh::Mesh(std::vector<Vector3> nvertices, std::vector<int> ntriangles) {
	if (size(nvertices) >= 3) {
		vertices = nvertices;
	}
	if (size(ntriangles) % 3 == 0) {
		triangles = ntriangles;
	}
}