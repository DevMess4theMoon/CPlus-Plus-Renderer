#include "RenderObject.h"
#include <list>
RenderObject::RenderObject(Color nc, std::list<Vector3> ncoordinates) {
	c = nc;
	coordinates = ncoordinates;
	auto it1 = ncoordinates.begin();
	Vector3 a = *it1;
	auto it2 = ncoordinates.begin();
	std::advance(it2, 1);
	Vector3 b = *it2;
	auto it3 = ncoordinates.begin();
	std::advance(it3, 2);
	Vector3 c = *it3;
	Vector3 U = b - a;
	Vector3 V = c - a;
	normal = Vector3(
		(U.y * V.z) - (U.z * V.y),
		(U.z * V.x) - (U.x * V.z),
		(U.x * V.y) - (U.y * V.x)
	);
}