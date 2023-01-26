#pragma once
#include "Color.h"
#include "Vector2.h" 
#include "Vector3.h" 
#include <vector>
class RenderObject
{
public:
	Color c;
	std::vector<Vector2> coordinates;
	RenderObject(Color nc, std::vector<Vector2>);
	RenderObject() = default;
};

