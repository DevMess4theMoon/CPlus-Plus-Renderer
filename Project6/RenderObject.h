#pragma once
#include "Color.h"
#include "Vector3.h"
#include <list>
class RenderObject
{
public:
	Color c;
	std::list<Vector3> coordinates;
	Vector3 normal;
	RenderObject(Color nc, std::list<Vector3> ncoordinates);
	RenderObject() = default;
};

