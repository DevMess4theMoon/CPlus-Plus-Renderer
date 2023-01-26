#pragma once
#include "RenderObject.h"
#include "Mesh.h"
#include <vector>
class RenderEngine
{
public:
	std::vector<RenderObject> renderQueue;
	void AddToRenderQueue(RenderObject object);
	void AddListToRenderQueue(std::vector<RenderObject> objects);
	static std::vector<RenderObject> ConvertMeshToRenderObjects(Mesh mesh);
};

