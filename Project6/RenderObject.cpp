#include "RenderObject.h"
RenderObject::RenderObject(Color nc, std::vector<Vector2> ncoordinates) {
	c = nc;
	coordinates.push_back(ncoordinates[0]);
	coordinates.push_back(ncoordinates[1]);
	coordinates.push_back(ncoordinates[2]);
	//normal = Vector3(
		//(U.y * V.z) - (U.z * V.y),
		//(U.z * V.x) - (U.x * V.z),
		//(U.x * V.y) - (U.y * V.x)
	//);
}