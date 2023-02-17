#include "Mesh.h"
#include <algorithm>
Mesh::Mesh(std::vector<Vector3> nvertices, std::vector<int> ntriangles) {
	if (size(nvertices) >= 3) {
		vertices = nvertices;
	}
	if (size(ntriangles) % 3 == 0) {
		triangles = ntriangles;
	}
}
Vector3 Mesh::calculateCenter(Mesh mesh) {
    std::vector<float> xValues, yValues, zValues;
    for (int i = 0; i < mesh.vertices.size(); i++) {
        xValues.push_back(mesh.vertices[i].x);
        yValues.push_back(mesh.vertices[i].y);
        zValues.push_back(mesh.vertices[i].z);
    }
    std::sort(xValues.begin(), xValues.end());
    std::sort(yValues.begin(), yValues.end());
    std::sort(zValues.begin(), zValues.end());

    int middle = mesh.vertices.size() / 2;
    return Vector3(xValues[middle], yValues[middle], zValues[middle]);
}